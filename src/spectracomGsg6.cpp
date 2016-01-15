#include "spectracom/spectracomGsg6.hpp"

namespace spectracom {
  
  bool Spectracom::connect(std::string remoteIp, uint16_t remotePort) {
    std::stringstream out;
    // Connect boost signal
    connection_.receivedMessage.connect(boost::bind(&Spectracom::parseIncomingData, this, _1, _2));
    
    remoteIp_ = remoteIp;
    remotePort_ = remotePort;
    
    // Create TCP connection
    if (connection_.connect(remoteIp, remotePort)) {
      out << "Connected to device at " << remoteIp << " : " << remotePort;
      log(out.str(), LogLevel::Info);
      return true;
    }
    out << "Failed to connect to device at " << remoteIp << " : " << remotePort;
    log(out.str(), LogLevel::Error);
    return false;
  }
  
  bool Spectracom::reConnect(size_t max_attempts) {
    static size_t attempts = 0;
    if (attempts >= max_attempts) { // return false if max attempts is reached
      return false;
    }
    attempts++;
    
    log("Attempting to reconnect to device.",LogLevel::Info);
    connection_.receivedMessage.disconnect_all_slots();
    connection_.disconnect();
    
    if (!connect(remoteIp_, remotePort_)) {
      reConnect(max_attempts);
    }
    return true; // return true if successfully connected
  }
  
  void Spectracom::send(std::string data) {
    std::stringstream output;
    
    if (isConnected()) {
      if (connection_.send(data)) {
        output << "In Spectracom::send(): Sent message " << data;
        log(output.str(), LogLevel::Debug);
        return;
      }
    }
      output  << "In Spectracom::send(): Faild to send message " << data;
      log(output.str(), LogLevel::Error);
    
    if(reConnect()) { // resend data if successfully reconnected
      send(data);
    }
    
    // Throw exception if connection unavailable
    throw ConnectionException();
  }
  
  void Spectracom::parseIncomingData(uint8_t *message, size_t length) {
    try {
      
      if (*message == '\n') {
//        log("Got only endline char.", LogLevel::Debug);
        return;
      }
      
      std::string msgString ((char*)message, length);
      log(msgString, LogLevel::Debug);
      
      if(parseErrorMessage(msgString)) { // Look for error message
        return;
        
      }
      
      // Query response received
      { // lock scope
        std::unique_lock<std::mutex> lock(queryResponseMutex_);
        queryResponse_ = msgString;
        queryResponseCondition_.notify_all();
      }

    } catch (std::exception &e) {
      std::stringstream output;
      output << "Error in Spectracom::parseIncomingData(): " << e.what();
      log(output.str(), LogLevel::Error);
    }
    return;
  }

  bool Spectracom::parseErrorMessage(std::string &message) {
    try {
      // Search for message in errorMsgStringArray
      const std::string *index = std::find(errorIds::msgStringArray.begin(),
                                           errorIds::msgStringArray.end(),
                                           message);
      
//      log("parseErrorMessage() : ", LogLevel::Debug);
//      log(message, LogLevel::Debug);
      
      // If no message found return
      if (*index == *errorIds::msgStringArray.end()) {
        log("No Error message found.", LogLevel::Debug);
        return false;
      }

      // Store error message in container error_ and notify queryError()
      { // lock scope
        std::unique_lock<std::mutex> lock(queryResponseMutex_);
        error_.errorString = message;
        error_.id = toErrorEnum(message.substr(0,message.find(commaDelimiter)));
        
//        std::stringstream debug1;
//        debug1  << "Parsed ID = " << message.substr(0,message.find(commaDelimiter))
//                << std::endl << "Parsed string = " << error_.errorString;
//        log(debug1.str(), LogLevel::Debug);
        errorCondition_.notify_all();
      }
      return true;
    } catch (std::exception &e) {
      std::stringstream output;
      output << "Error in Spectracom::parseErrorMessage(): " << e.what();
      log(output.str(), LogLevel::Error);
      return false;
    }
  }
  
  
  // -------------------------------------------------
  // Queries
  
  void Spectracom::queryError() {
    errorIds::ErrorMsg error;
    
    // Send query message
    send(toQueryIdString(queryIds::MsgIds::System_Error) + queryIds::queryIndicator
         + '\n');
    
    try { // Process response
      std::unique_lock<std::mutex> lock(errorMutex_);
      
      // If response is received
      if (errorCondition_.wait_for(lock, std::chrono::seconds((int)RESPONSE_TIMEOUT))
          == std::cv_status::no_timeout)
      {
        error = error_;
        error_ = errorIds::ErrorMsg(); // clear struct
        std::stringstream out;
        out << "Spectracom Error: " << error.errorString << " with ID " << toErrorIdString(error.id);
        log(out.str(), LogLevel::Error);
        if (error.id != errorIds::MsgIds::NoError) {
          throw SpectracomErrorException(error.errorString);
        }
      } else {
        std::stringstream connectionError;
        connectionError << "No response to queryError() received before timeout.";
        log(connectionError.str(), LogLevel::Error);
        return;
      }
    } catch (std::exception &e) {
      std::stringstream output;
      output << "Error in Spectracom::queryError(): " << e.what();
      log(output.str(), LogLevel::Error);
      return;
    }

  }
  
  
  bool Spectracom::query(std::string &queryStr, std::string &responseStr) {
    // send query and wait for response
    send(queryStr + queryIds::queryIndicator + endlineIndicator);
    try {
        std::unique_lock<std::mutex> lock(queryResponseMutex_);

        // If query response received
        if (queryResponseCondition_.wait_for(lock, std::chrono::seconds((int)RESPONSE_TIMEOUT))
            == std::cv_status::no_timeout)
        {
          responseStr = queryResponse_;
          queryResponse_.clear();
          return true;
        }
    } catch (std::exception &e) {
      std::stringstream output;
      output << "Error in Spectracom::query(): " << e.what();
      log(output.str(), LogLevel::Error);
    }
    // Response not received before timeout, check for device error
    queryError();
    return false;
  }
  
  bool Spectracom::queryIdentification() {
    try {
      
      std::string querystr =  toQueryIdString(queryIds::MsgIds::Common_Identification);

      std::string responseStr;
      if (query(querystr, responseStr)) {
        // TODO
        log(responseStr, LogLevel::Debug);
        return true;
      }
    } catch (std::exception &e) {
      std::stringstream error;
      error << "Error in Spectracom::queryIdentification(): " << e.what();
      log(error.str(), LogLevel::Error);
    }
    return false;
  }
  
  bool Spectracom::querySelfTest(SelfTest &testResult) {
    std::string querystr =  toQueryIdString(queryIds::MsgIds::Common_Identification);
    
    std::string responseStr;
    
    if(query(querystr, responseStr)) {
      if (responseStr == "0") {
        testResult = SelfTest::NoError;
      } else if (responseStr == "1") {
        testResult  = SelfTest::ErrorInReferenceClock;
      } else {
        log("Invalid response to querySelfTest", LogLevel::Error);
        return false;
      }
      return true;
    }
    return false;
  }
  
  bool Spectracom::queryTransmitPower(double &power) {
    std::string querystr =  toQueryIdString(queryIds::MsgIds::Source_TransmitPower);
    std::string responseStr;
    try {
      if(query(querystr, responseStr)) {
        std::string::size_type sz;     // alias of size_t
        power = std::stod(responseStr, &sz);
        std::stringstream out;
        out << "Power = " << power << " dBm";
        log(out.str(), LogLevel::Debug);
        return true;
      }
    } catch (std::exception &e) {
      std::stringstream error;
      error << "Error in Spectracom::queryTransmitPower(): " << e.what();
      log(error.str(), LogLevel::Error);
    }
    return false;
  }
  
  bool Spectracom::queryPpsOutput(PpsFrequency &pps) {
    std::string querystr =  toQueryIdString(queryIds::MsgIds::Source_PpsOutput);
    std::string responseStr;
    try {
      if(query(querystr, responseStr)) {
        std::string::size_type sz;     // alias of size_t
        pps = (PpsFrequency)std::stoul(responseStr, &sz);
        std::stringstream out;
        out << "PPS Frequency = " << (uint16_t)pps;
        log(out.str(), LogLevel::Debug);
        return true;
      }
    } catch (std::exception &e) {
      std::stringstream error;
      error << "Error in Spectracom::queryPpsOutput(): " << e.what();
      log(error.str(), LogLevel::Error);
    }
    return false;
  }
  
  bool Spectracom::queryExternalAttenuation(double &attenuation) {
    std::string querystr =  toQueryIdString(queryIds::MsgIds::
                                     Source_ExternalAttenuation);
    std::string responseStr;
    try {
      if(query(querystr, responseStr)) {
        std::string::size_type sz;     // alias of size_t
        attenuation = std::stod(responseStr, &sz);
        std::stringstream out;
        out << "External attenuation = " << attenuation << " dB";
        log(out.str(), LogLevel::Debug);
        return true;
      }
    } catch (std::exception &e) {
      std::stringstream error;
      error << "Error in Spectracom::queryExternalAttenuation(): " << e.what();
      log(error.str(), LogLevel::Error);
    }
    return false;
  }
  
  bool Spectracom::queryCarrierToNoise(double &cno) {
    std::string querystr =  toQueryIdString(queryIds::MsgIds::
                                     Source_Noise_Cno);
    std::string responseStr;
    try {
      if(query(querystr, responseStr)) {
        std::string::size_type sz;     // alias of size_t
        cno = std::stod(responseStr, &sz);
        std::stringstream out;
        out << "Carrier to Noise = " << cno << " dBHz";
        log(out.str(), LogLevel::Debug);
        return true;
      }
    } catch (std::exception &e) {
      std::stringstream error;
      error << "Error in Spectracom::queryCarrierToNoise(): " << e.what();
      log(error.str(), LogLevel::Error);
    }
    return false;
  }
  
  bool Spectracom::querySignalGenerator(signalGeneratorStateResponse::Enum
                                        &state) {
    
    std::string querystr =  toQueryIdString(queryIds::MsgIds::
                                     Source_Channel_Control);
    std::string responseStr;
    try {
      if(query(querystr, responseStr)) {
        state = toSignalGeneratorStateResponseEnum(responseStr);
        std::stringstream out;
        out << "Signal Generator state = " << responseStr;
        log(out.str(), LogLevel::Debug);
        return true;
      }
    } catch (std::exception &e) {
      std::stringstream error;
      error << "Error in Spectracom::querySignalGenerator(): " << e.what();
      log(error.str(), LogLevel::Error);
    }
    return false;
  }
  
  bool Spectracom::queryLoadedScenario(std::string &scenario) {
    
    std::string querystr =  toQueryIdString(queryIds::MsgIds::Source_Scenario_Load);
    try {
      if(query(querystr, scenario)) {
        std::stringstream out;
        out << "Current loaded scenario = " << scenario;
        log(out.str(), LogLevel::Debug);
        return true;
      }
    } catch (std::exception &e) {
      std::stringstream error;
      error << "Error in Spectracom::queryLoadedScenario(): " << e.what();
      log(error.str(), LogLevel::Error);
    }
    return false;
  }
  
  
  
  
  
  // -------------------------------------------------
  // Commands
  
  bool Spectracom::command(std::string &str) {
    // send command and check that no error occured
    try {
      send(str + endlineIndicator);
      
      // Check that command was successful
      queryError();
      
    } catch (std::exception &e) {
      std::stringstream output;
      output << "Error in Spectracom::command(): " << e.what();
      log(output.str(), LogLevel::Error);
      return false;
    }
    return true;
  }
  
  bool Spectracom::commandClearStatus() {
    std::string cmdStr = toCommandString(commandIds::MsgIds::Common_ClearStatus);
    return command(cmdStr);
  }
  
  bool Spectracom::commandResetDevice() {
    std::string cmdStr = toCommandString(commandIds::MsgIds::Common_Reset);
    return command(cmdStr);
  }
  
  bool Spectracom::commandWaitToContinue() {
    std::string cmdStr = toCommandString(commandIds::MsgIds::Common_WaitToContinue);
    return command(cmdStr);
  }
  
  bool Spectracom::commandTransmitPower(double &power) {
    if ((power < -160) || (power > -123.2)) {
      log("In Spectracom::commandTransmitPower() : Power must be within -160 to -123.2 dBm.", LogLevel::Error);
      return false;
    }
    try {
      std::string cmdStr;
      cmdStr =  toCommandString(commandIds::MsgIds::Source_TransmitPower)
                + whitespaceDelimiter + std::to_string(power);    
      return command(cmdStr);
    } catch (std::exception &e) {
      std::stringstream output;
      output << "Error in Spectracom::commandTransmitPower(): " << e.what();
      log(output.str(), LogLevel::Error);
      return false;
    }
  }
  
  bool Spectracom::commandPpsOutput(PpsFrequency &pps) {
    try {
      std::string cmdStr;
      cmdStr =  toCommandString(commandIds::MsgIds::Source_PpsOutput)
                + whitespaceDelimiter + std::to_string((uint16_t)pps);
      return command(cmdStr);
    } catch (std::exception &e) {
      std::stringstream output;
      output << "Error in Spectracom::commandPpsOutput(): " << e.what();
      log(output.str(), LogLevel::Error);
      return false;
    }
  }
  
  bool Spectracom::commandExternalAttenuation(double &attenuation) {
    if ((attenuation < 0) || (attenuation > 30)) {
      log("In Spectracom::commandExternalAttenuation() : Power must be within 0 to 30 dB.",
          LogLevel::Error);
      return false;
    }
    try {
      std::string cmdStr;
      cmdStr =  toCommandString(commandIds::MsgIds::Source_ExternalAttenuation)
                + whitespaceDelimiter + std::to_string(attenuation);
      return command(cmdStr);
    } catch (std::exception &e) {
      std::stringstream output;
      output << "Error in Spectracom::commandExternalAttenuation(): " << e.what();
      log(output.str(), LogLevel::Error);
      return false;
    }
  }
  
  bool Spectracom::commandCarrierToNoise(double &cno) {
    if ((cno < 0) || (cno > 56)) {
      log("In Spectracom::commandCarrierToNoise() : Power must be within 0 to 56 dB.",
          LogLevel::Error);
      return false;
    }
    try {
      std::string cmdStr;
      cmdStr =  toCommandString(commandIds::MsgIds::Source_Noise_Cno)
                + whitespaceDelimiter + std::to_string(cno);
      return command(cmdStr);
    } catch (std::exception &e) {
      std::stringstream output;
      output << "Error in Spectracom::commandCarrierToNoise(): " << e.what();
      log(output.str(), LogLevel::Error);
      return false;
    }
  }
  
  bool Spectracom::commandSignalGenerator(signalGeneratorStateCommands::Enum &state) {
    try {
      std::string cmdStr;
      cmdStr =  toCommandString(commandIds::MsgIds::Source_Channel_Control)
                + whitespaceDelimiter
                + signalGeneratorStateCommands::stringArray[(size_t)state];
      return command(cmdStr);
    } catch (std::exception &e) {
      std::stringstream output;
      output << "Error in Spectracom::commandSignalGenerator(): " << e.what();
      log(output.str(), LogLevel::Error);
      return false;
    }
  }
  
  bool Spectracom::commandLoadScenario(std::string &scenario) {
    try {
      std::string cmdStr;
      cmdStr =  toCommandString(commandIds::MsgIds::Source_Scenario_Load)
      + whitespaceDelimiter + scenario;
      return command(cmdStr);
    } catch (std::exception &e) {
      std::stringstream output;
      output << "Error in Spectracom::commandLoadScenario(): " << e.what();
      log(output.str(), LogLevel::Error);
      return false;
    }
  }
  
  
  // -------------------------------------------------
  // Conversions
  
  std::string Spectracom::toQueryIdString(queryIds::MsgIds inputEnum) {
    return queryIds::msgIdStringArray.at((std::size_t)inputEnum);
  }
  
  queryIds::MsgIds Spectracom::toQueryIdEnum(std::string inputString) {
    const std::string *result = std::find(queryIds::msgIdStringArray.begin(),
                                          queryIds::msgIdStringArray.end(),
                                          inputString);
    //      if (result == stringArray.end()) {
    //        return ;
    //      } // TODO: Add exception throw for if string not valid
    
    return (queryIds::MsgIds)(std::distance(queryIds::msgIdStringArray.begin(),
                                            result));
  }
  
  std::string Spectracom::toFullErrorString(errorIds::MsgIds msgId) {
    return errorIds::msgStringArray.at((std::size_t)msgId);
  }
  
  std::string Spectracom::toErrorIdString(errorIds::MsgIds inputEnum) {
    return errorIds::msgIdStringArray.at((std::size_t)inputEnum);
  }
  
  errorIds::MsgIds Spectracom::toErrorEnum(std::string inputString) {
    const std::string *result = std::find(errorIds::msgIdStringArray.begin(),
                                          errorIds::msgIdStringArray.end(),
                                          inputString);
    if (result == errorIds::msgIdStringArray.end()) {
      return errorIds::MsgIds::UndefinedError;
    } // TODO: Add exception throw for if string not valid
    
    return (errorIds::MsgIds)(std::distance(errorIds::msgIdStringArray.begin(),
                                            result));
  }
  
  std::string Spectracom::toOptionString(deviceOptions::Enum inputEnum) {
    return deviceOptions::stringArray[(std::size_t)inputEnum];
  }
  
  deviceOptions::Enum Spectracom::toOptionEnum(std::string inputString) {
    const std::string *result = std::find(deviceOptions::stringArray.begin(),
                                          deviceOptions::stringArray.end(),
                                          inputString);
    //      if (result == stringArray.end()) {
    //        return ;
    //      } // TODO: Add exception throw for if string not valid
    
    return (deviceOptions::Enum)( std::distance(
                                                deviceOptions::stringArray.begin(),
                                                result));
  }
  
  std::string Spectracom::toCommandString(commandIds::MsgIds inputEnum) {
    return commandIds::msgIdStringArray[(std::size_t)inputEnum];
  }
  
  commandIds::MsgIds Spectracom::toCommandEnum(std::string inputString) {
    const std::string *result = std::find(commandIds::msgIdStringArray.begin(),
                                          commandIds::msgIdStringArray.end(),
                                          inputString);
    //      if (result == stringArray.end()) {
    //        return ;
    //      } // TODO: Add exception throw for if string not valid
    
    return (commandIds::MsgIds)(std::distance(commandIds::msgIdStringArray.begin(),
                                              result));
  }
  
  signalGeneratorStateResponse::Enum
  Spectracom::toSignalGeneratorStateResponseEnum(std::string inputString) {
    const std::string *result = std::find(signalGeneratorStateResponse::stringArray.begin(),
                                          signalGeneratorStateResponse::stringArray.end(),
                                          inputString);
    //      if (result == stringArray.end()) {
    //        return ;
    //      } // TODO: Add exception throw for if string not valid
    
    return (signalGeneratorStateResponse::Enum)(std::distance(signalGeneratorStateResponse::stringArray.begin(),
                                                              result));
  }
  
} // end namespace spectracom