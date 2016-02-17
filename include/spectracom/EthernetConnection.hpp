//-----------------------------------------------------------------------------
//                                UNCLASSIFIED
//-----------------------------------------------------------------------------
//===-- spectracom/EthernetConnection.hpp -
//                                  EthernetConnection class definition --===//
//
// Copyright (C) Integrated Solutions for Systems, Inc - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
//===---------------------------------------------------------------------===//
///
/// \file
/// \brief    Contains the declaration of the EthernetConnection class.
/// \details  The EthernetConnection class is a wrapper for PracticalSocket,
///           adapting it to the SCPI ethernet commmunications protocol used 
///           by the Spectracom GSG simulator. If using the GSG 10 Hz epoch
///           rate, it is recommended to use USB communications instead.
///
/// Chris Collins <chris.collins@is4s.com>
/// January 5, 2016
///
//===---------------------------------------------------------------------===//
#ifndef ETHERNET_CONNECTION_HPP
#define ETHERNET_CONNECTION_HPP

#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>

#include "spectracom/PracticalSocket.h"
#include "logutils/logutils.hpp"

namespace bs2 = boost::signals2;

namespace spectracom {

/// Defines a function type for external logging functions
// typedef std::function<void(const std::string &)> LoggingHandler;

/// \brief Class to disseminate GNSS data over a network
///
/// The EthernetConnection class is a wrapper for PracticalSocket,
/// adapting it to the SCPI ethernet commmunications protocol used 
/// by the Spectracom GSG simulator.
class EthernetConnection {

public:
  /// \brief Constructs the ~EthernetConnection object
  EthernetConnection(int bufferSize=1000)
  : isConnected_(false),
    running_(false)
  {
    incomingBufferSize_ = bufferSize;
    log_ = logutils::printLogToStdOut;
  };
  
  /// \brief Called on destruction of the ~EthernetConnection object
  ~EthernetConnection(){};

  /// \brief Open network sockets and start the read thread
  /// \returns true if the network sockets are successfully opened
  bool connect(std::string remoteIp, uint16_t remotePort);

  bool isConnected(){return isConnected_;};
  
  void disconnect();
  
  void setRemoteIp(std::string ip){remoteIp_ = ip;};
  void setRemotePort(uint16_t port){remotePort_ = port;}; 

  void setLogCallback(const logutils::LogCallback& logCallback) {
    log_ = logCallback;
  };

  /// Signal generated when a message is received on the network interface
  bs2::signal<void(uint8_t *, size_t)> receivedMessage;

  //---------------------------------------------------------------------------
  // Logging Signals

  /// \brief Send a packet to the address from remoteIp_ on remotePort_
  /// \param  data    Pointer to a char array containing the data to send
  /// \param  length  Length of the char array
  /// \returns true if the packet is successfully sent
  bool send(uint8_t *data, const size_t length);

  bool send(std::string data) {
    return send((uint8_t *)data.c_str(), data.length());
  };

protected:

  // Loop to listen for incoming data on the multicast socket
  void listenToSocket();

  // TCP Socket object from PracticalSocket
  TCPSocket socket_;
  
  // True if the socket is connected
  bool isConnected_;
  // True if the listening thread is running.
  bool running_;
  // Protects isConnected_ and running_
  std::mutex connectionMutex_;

  // Incoming buffer size (Max message size)
  int incomingBufferSize_;

  //---------------------------------------------------------------------------
  // Network settings

  /// Multicast group IP
  std::string remoteIp_;
  /// Multicast port number
  uint16_t remotePort_;
  
  logutils::LogCallback log_;

};
} // namespace spectracom
#endif // ETHERNET_CONNECTION_HPP
//-----------------------------------------------------------------------------
//                                  UNCLASSIFIED
//-----------------------------------------------------------------------------
