//-----------------------------------------------------------------------------
//                                UNCLASSIFIED
//-----------------------------------------------------------------------------
//==--- src/EthernetConnection.cpp - EthernetConnection class definition--===//
//
// Copyright (C) Integrated Solutions for Systems, Inc - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
//===---------------------------------------------------------------------===//
// This file contains the declaration of the EthernetConnection class.
//
// Chris Collins <chris.collins@is4s.com>
// January 5, 2016
//
//===---------------------------------------------------------------------===//
#include "spectracom/EthernetConnection.hpp"

namespace spectracom {

bool EthernetConnection::connect(std::string remoteIp, uint16_t remotePort) {

  log_("Establishing network connection.", logutils::LogLevel::Info);
  
  setRemoteIp(remoteIp);
  setRemotePort(remotePort);

  // connect to socket
  try {
    std::stringstream Out;
    Out << "Connected to " << remoteIp_ << ":" << remotePort_;
    log_(Out.str(), logutils::LogLevel::Info);

    socket_.connect(remoteIp_, remotePort_);
    
  } catch (SocketException &e) {
    isConnected_ = false;
    std::stringstream output;
    output << "Error connecting to " << remoteIp << " : " << remotePort_
           << ":" << e.what();
    log_(output.str(), logutils::LogLevel::Error);
    return false;
  }
  
  { // lock scope
    std::unique_lock<std::mutex> lock(connectionMutex_);
    isConnected_ = true;
    running_ = true;
  }
  
  // start listening thread
  std::thread listenThread(&EthernetConnection::listenToSocket, this);
  listenThread.detach();
    
  return true;
}

void EthernetConnection::disconnect() {
  {
    std::unique_lock<std::mutex> lock(connectionMutex_);
    running_ = false;
    isConnected_ = false;
  }
}
  
bool EthernetConnection::send(uint8_t *data, size_t length) {
  try {
    socket_.send(data, length);
  } catch (SocketException &e) {
    std::stringstream output_err;
    output_err << "EthernetConnection: Error sending data: "
               << e.what();
    log_(output_err.str(), logutils::LogLevel::Error);
    return false;
  }

  return true;
}

void EthernetConnection::listenToSocket() {

  uint8_t buffer[incomingBufferSize_];
  size_t bytesReceived;

  while (running_) {
    std::unique_lock<std::mutex> lock(connectionMutex_);
    try {
      // Read data from the socket
      bytesReceived = socket_.recv(buffer, incomingBufferSize_);
    } catch (SocketException &e) {
      std::stringstream output_err;
      output_err << "EthernetConnection: Error receiving data: "
                 << e.what();
      log_(output_err.str(), logutils::LogLevel::Error);
      break;
    }
    if (bytesReceived > 0)  {
      receivedMessage(buffer, bytesReceived);
    }
  }
  disconnect();
  log_("Multicast listening thread exiting.", logutils::LogLevel::Info);
}


}
//-----------------------------------------------------------------------------
//                                UNCLASSIFIED
//-----------------------------------------------------------------------------