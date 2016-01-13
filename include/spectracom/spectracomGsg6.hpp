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
/// \brief
/// \details
///
/// \author   Chris Collins <chris.collins@is4s.com>
/// \date     January 2016
///
///===---------------------------------------------------------------------===//

#ifndef SPECTRACOM_GSG6_HPP
#define SPECTRACOM_GSG6_HPP

//#include <string>
#include <iostream>
#include <thread>

//#include <functional>
//#include <boost/signals2.hpp>

#include "spectracom/EthernetConnection.hpp"
#include "spectracom/spectracomGsg6Protocol.hpp"
#include "spectracom/ConnectionException.hpp"

namespace spectracom {

  const size_t MAX_BUFFER_SIZE = 1000;
  const double RESPONSE_TIMEOUT = 1; // [sec]
  
  class Spectracom {
  public:
    Spectracom() {};
    ~Spectracom(){};
    
    /// \brief  Opens connection to simulator
    ///
    /// \param  remoteIp    Ip address of simulator
    /// \param  remotePort  Port of simulator
    ///
    /// /returns  True if successfully connected
    bool connect(std::string remoteIp, uint16_t remotePort);

    bool reConnect();
    
    bool isConnected(){return connection_.isConnected();};
    
    /// \brief  Sends data to simulator
    ///
    /// \param  data    Data to send to device
    /// \param  length  Length of data to send
    ///
    /// \returns  True if successfully sent
    bool send(std::string data);
    bool send(uint8_t *data, const size_t length);

    /// \brief  Signal generated for log message occurance
    bs2::signal<void(const std::string &, const LogLevel &)> log;
    
    // -------------------------------------------------
    // Queries
    
    /// \brief  Query device for Error
    ///
    /// \param  errorResponse Error MsgId returned from device
    ///
    /// \returns  True if query is successfull
    bool queryError(errorIds::MsgIds &errorResponse);
    
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
    bool querySelfTest(SelfTest &testResult);
    
    /// \brief  Query transmit power
    ///
    /// \param  power   Transmit power in dBm [-160 to -123.2]
    ///
    /// \return   True if successfull
    bool queryTransmitPower(double &power);
    
    /// \brief  Query PPS output rate
    ///
    /// \param  pps   Enum of PPS options {1, 10, 100, 1000} PPS
    ///
    /// \return   True if successfull
    bool queryPpsOutput(PpsFrequency &pps);
    
    /// \brief  Query External attenuation
    ///
    /// \param  attenuation External attenuation on output RF signal [0-30 dB]
    ///
    /// \return   True if successfull
    bool queryExternalAttenuation(double &attenuation);
    
    /// \brief  Query Max Carrier to Noise
    ///
    /// \param  cno Max carrier to noise of signals [0.0-56.0 dBHz]
    ///
    /// \return   True if successfull
    bool queryCarrierToNoise(double &cno);
    
    /// \brief  Query Signal Generator status
    ///
    /// \param  state   Current state of signal generator defined in
    ///
    /// \return   True if successfull
    bool querySignalGenerator(signalGeneratorStateResponses::Enum &state);
    
    /// \brief  Query current loaded scenario
    ///
    /// \param  scenario   Current loaded scenario
    ///
    /// \return   True if successfull
    bool queryLoadedScenario(std::string &scenario);
    
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
    bool commandTransmitPower(double &power);
    
    /// \brief  Set PPS output rate
    ///
    /// \param  pps   Enum of PPS options {1, 10, 100, 1000} PPS
    ///
    /// \return   True if successfull
    bool commandPpsOutput(PpsFrequency &pps);
    
    /// \brief  Set External attenuation
    ///
    /// \param  attenuation External attenuation on output RF signal [0-30 dB]
    ///
    /// \return   True if successfull
    bool commandExternalAttenuation(double &attenuation);
    
    /// \brief  Set Max Carrier to Noise
    ///
    /// \param  cno Max carrier to noise of signals [0.0-56.0 dBHz]
    ///
    /// \return   True if successfull
    bool commandCarrierToNoise(double &cno);
    
    /// \brief  Set Signal Generator state
    ///
    /// \param  state   Desired state of signal generator {START,STOP,ARM}
    ///
    /// \return   True if successfull
    bool commandSignalGenerator(signalGeneratorStateCommands::Enum &state);
    
    /// \brief  Load scenario
    ///
    /// \param  scenario   Name of scenario to load
    ///
    /// \return   True if successfull
    bool commandLoadScenario(std::string &scenario);

    
  private:
    
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
    EthernetConnection connection_ {(int)MAX_BUFFER_SIZE};
    
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
    
    
    // -------------------------------------------------
    // Exceptions
    ConnectionException connectionException_;
    
  }; // end class Spectracom
} // end namespace spectracom
#endif // SPECTRACOM_GSG6_HPP
///-----------------------------------------------------------------------------
///                                UNCLASSIFIED
///-----------------------------------------------------------------------------