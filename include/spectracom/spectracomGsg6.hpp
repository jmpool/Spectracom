///-----------------------------------------------------------------------------
///                                UNCLASSIFIED
///-----------------------------------------------------------------------------
///==------------------- spectracomGsg6/spectracomGsg6.hpp -----------------==//
///
/// Copyright (C) Integrated Solutions for Systems, Inc - All Rights Reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited.
/// Proprietary and confidential.
///
///===---------------------------------------------------------------------===//
///
/// \file
/// \brief    Interface to the Spectracom GSG6 GNSS Simulator
/// \author   Chris Collins <chris.collins@is4s.com>
/// \date     January 2016
///
///===---------------------------------------------------------------------===//

#ifndef SPECTRACOM_GSG6_HPP
#define SPECTRACOM_GSG6_HPP

#include <iostream>
#include <thread>
#include <fstream>

#include "spectracom/EthernetConnection.hpp"
#include "spectracom/spectracomGsg6Protocol.hpp"
#include "spectracom/exceptions/ConnectionException.hpp"
#include "spectracom/exceptions/SpectracomErrorException.hpp"
#include "logutils/logutils.hpp"

namespace spectracom {

  const size_t MAX_BUFFER_SIZE = 1000;
  const double RESPONSE_TIMEOUT = 1; // [sec]
  
  class Spectracom {
  public:
    Spectracom(const logutils::LogCallback& log = logutils::printLogToStdOut)
    : connection_(MAX_BUFFER_SIZE, log),
      log_(log){};

    ~Spectracom(){};
    
    /// \brief  Opens connection to simulator
    ///
    /// \param  remoteIp    Ip address of simulator
    /// \param  remotePort  Port of simulator
    ///
    /// /returns  True if successfully connected
    bool connect(std::string remoteIp, uint16_t remotePort);
    
    bool isConnected(){return connection_.isConnected();};
    
    /// \brief  Sends data to simulator
    ///
    /// \param  data    Data to send to device
    /// \param  length  Length of data to send
    ///
    /// \returns  void
    void send(std::string data);

    /// \brief  Set log_ callback
    ///
    /// \param  logCallback   Function to set as log_
    ///
    /// \return void
    void setLogCallback(logutils::LogCallback logCallback);
    
    /// \brief  Parse messages from file
    ///
    /// \param  filename  Name of file to parse
    ///
    /// \return void
    void parseFromFile(std::string filename);
    
    // -------------------------------------------------
    // Queries
    
    /// \brief  Query device for Error
    ///
    /// \param  errorResponse Error MsgId returned from device
    ///
    /// \returns  True if query is successfull
    void queryError();
    
    /// \brief  [*IDN?] Simulator Identification Query
    ///
    /// \param  
    ///
    /// \returns  True if successfull
    bool queryIdentification();
    
    /// \brief  Internal self test
    ///
    /// \param  testResult  Response from device
    ///
    /// \returns True if passes, False if fails test
    bool querySelfTest(SelfTest testResult);
    
    /// \brief  Query transmit power
    ///
    /// \param  power   Transmit power in dBm [-160 to -123.2]
    ///
    /// \return   True if successfull
    bool queryTransmitPower(double power);
    
    /// \brief  Query PPS output rate
    ///
    /// \param  pps   Enum of PPS options {1, 10, 100, 1000} PPS
    ///
    /// \return   True if successfull
    bool queryPpsOutput(PpsFrequency pps);
    
    /// \brief  Query External attenuation
    ///
    /// \param  attenuation External attenuation on output RF signal [0-30 dB]
    ///
    /// \return   True if successfull
    bool queryExternalAttenuation(double attenuation);
    
    /// \brief  Query Max Carrier to Noise
    ///
    /// \param  cno Max carrier to noise of signals [0.0-56.0 dBHz]
    ///
    /// \return   True if successfull
    bool queryCarrierToNoise(double cno);
    
    /// \brief  Query Signal Generator status
    ///
    /// \param  state   Current state of signal generator defined in
    ///
    /// \return   True if successfull
    bool querySignalGenerator(signalGeneratorStateResponse::Enum state);
    
    /// \brief  Query current loaded scenario
    ///
    /// \param  scenario   Current loaded scenario
    ///
    /// \return   True if successfull
    bool queryLoadedScenario(std::string scenario);
    
    // -------------------------------------------------
    // Commands
    
    /// \brief  Clears status data structures, event registers, and error queue
    ///
    /// \returns  True if successfull
    bool commandClearStatus();
    
    /// \brief  Reset the device
    ///
    /// \returns  True if successfull
    bool commandResetDevice();
    
    /// \brief  Wait until execution of previous commands finishes to continue
    ///
    /// \returns  True if successfull
    bool commandWaitToContinue();
    
    /// \brief  Sets transmit power
    ///
    /// \param  power   Transmit power in dBm [-160 to -123.2]
    ///
    /// \return   True if successfull
    bool commandTransmitPower(double power);
    
    /// \brief  Set PPS output rate
    ///
    /// \param  pps   Enum of PPS options {1, 10, 100, 1000} PPS
    ///
    /// \return   True if successfull
    bool commandPpsOutput(PpsFrequency pps);
    
    /// \brief  Set External attenuation
    ///
    /// \param  attenuation External attenuation on output RF signal [0-30 dB]
    ///
    /// \return   True if successfull
    bool commandExternalAttenuation(double attenuation);
    
    /// \brief  Set Max Carrier to Noise
    ///
    /// \param  cno Max carrier to noise of signals [0.0-56.0 dBHz]
    ///
    /// \return   True if successfull
    bool commandCarrierToNoise(double cno);
    
    /// \brief  Set Signal Generator state
    ///
    /// \param  state   Desired state of signal generator {START,STOP,ARM}
    ///
    /// \return   True if successfull
    bool commandSignalGenerator(signalGeneratorStateCommands::Enum state);
    
    /// \brief  Load scenario
    ///
    /// \param  scenario   Name of scenario to load
    ///
    /// \return   True if successfull
    bool commandLoadScenario(std::string scenario);

    /// \brief  Start scenario
    ///
    /// \return   True if successfull
    bool commandStartScenario();
    
    /// \brief  Stop scenario
    ///
    /// \return   True if successfull
    bool commandStopScenario();
    
    /// \brief  Hold scenario
    ///
    /// \return   True if successfull
    bool commandHoldScenario();
    
    /// \brief  Arm scenario
    ///
    /// \return   True if successfull
    bool commandArmScenario();
    
    // ------------------------------------------------------------------------
    // Conversion Methods
    
    /// \brief  Convert query Id enum to corresponding string
    ///
    /// \param  inputEnum   query message id to get string of
    ///
    /// \return   String query msg id
    std::string toQueryIdString(queryIds::MsgIds inputEnum);
    
    /// \brief  Convert query Id string to corresponding enum
    ///
    /// \param  inputString   query id string to get enum of
    ///
    /// \return   query msg id
    queryIds::MsgIds toQueryIdEnum(std::string inputString);
    
    /// \brief  Convert error Id enum to full message string
    ///
    /// \param  msgId   error message id to get string of
    ///
    /// \return   Full error message string
    std::string toFullErrorString(errorIds::MsgIds msgId);
 
    /// \brief  Convert error Id enum to id string
    ///
    /// \param  inputEnum   error message id to get string of
    ///
    /// \return   error message id string
    std::string toErrorIdString(errorIds::MsgIds inputEnum);
    
    /// \brief  Convert error Id string to corresponding enum
    ///
    /// \param  inputString   error id string to get enum of
    ///
    /// \return   error msg id enum
    errorIds::MsgIds toErrorEnum(std::string inputString);
  
    /// \brief  Convert options Id enum to id string
    ///
    /// \param  inputEnum   options message id to get string of
    ///
    /// \return   options message id string
    std::string toOptionString(deviceOptions::Enum inputEnum);
    
    /// \brief  Convert option Id string to corresponding enum
    ///
    /// \param  inputString   option id string to get enum of
    ///
    /// \return   option msg id enum
    deviceOptions::Enum toOptionEnum(std::string inputString);
    
    /// \brief  Convert command Id enum to id string
    ///
    /// \param  inputEnum   command message id to get string of
    ///
    /// \return   command message id string
    std::string toCommandString(commandIds::MsgIds inputEnum);
    
    /// \brief  Convert command Id string to corresponding enum
    ///
    /// \param  inputString   command id string to get enum of
    ///
    /// \return   command msg id enum
    commandIds::MsgIds toCommandEnum(std::string inputString);

    /// \brief  Convert signalGeneratorStateResponse Id string to enum
    ///
    /// \param  inputString   signalGeneratorStateResponse id string to get enum of
    ///
    /// \return   signalGeneratorStateResponse msg id enum
    signalGeneratorStateResponse::Enum
    toSignalGeneratorStateResponseEnum(std::string inputString);
    
    /// \brief  Convert string to scenarioControl Enum
    ///
    /// \param  inputString   scenarioControl option string
    ///
    /// \return scenarioControl enum value
    scenarioControl::Enum toScenarioControlEnum(std::string inputString);
    
    /// \brief  Convert scenarioControl Enum to string
    ///
    /// \param  inputEnum   scenarioControl enum option
    ///
    /// \return scenarioControl string
    std::string toScenarioControlString(scenarioControl::Enum inputEnum);
    

  private:
    
    /// \brief  Attempt to reconnect to device
    ///
    /// \param  max_attempts  Optional number of attempts to retry connecting
    ///
    /// \return True if successfully reconnected
    bool reConnect(size_t max_attempts=1);
    
    /// \brief  Send query and wait for response
    ///
    /// \param  queryStr    Query message to send
    /// \param  responseStr Response to query from device
    ///
    /// \returns  True if successfull
    bool query(std::string &queryStr, std::string &responseStr);
    
    /// \brief  Send command then query for error
    ///
    /// \param  str Command message to send
    ///
    /// \returns  True if command successfull
    bool command(std::string &str);
    
    /// \brief  Parse incoming data from device
    ///
    /// \param  message   Incoming data
    /// \param  length    Length of incoming data
    ///
    /// \returns  void
    void parseIncomingData(uint8_t *message, size_t length);
    
    /// \brief  Parse Error message and store in error_ object
    ///
    /// \param  message   Incoming message data
    ///
    /// \returns  True if successfully parsed
    bool parseErrorMessage(std::string &message);
    
    /// EthernetConnection object
    EthernetConnection connection_;
    
    /// Stores last query response
    std::condition_variable queryResponseCondition_;
    std::mutex queryResponseMutex_;
    std::string queryResponse_;
    
    /// Stores last Error response
    std::condition_variable errorCondition_;
    std::mutex errorMutex_;
    errorIds::ErrorMsg error_;    
    
    std::string remoteIp_;
    uint16_t remotePort_;
    
    logutils::LogCallback log_;
    
  }; // end class Spectracom
  
  inline void Spectracom::setLogCallback(logutils::LogCallback logCallback) {
    log_ = logCallback;
    connection_.setLogCallback(logCallback);
  }
  
} // end namespace spectracom
#endif // SPECTRACOM_GSG6_HPP
///-----------------------------------------------------------------------------
///                                UNCLASSIFIED
///-----------------------------------------------------------------------------