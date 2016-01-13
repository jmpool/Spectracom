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

EthernetConnection::EthernetConnection(int bufferSize)
    : isConnected_(false), running_(false)
  {
    incomingBufferSize_ = bufferSize;
  }

bool EthernetConnection::connect(std::string remoteIp, uint16_t remotePort) {

  log("Establishing network connection.", LogLevel::Info);
  
  setRemoteIp(remoteIp);
  setRemotePort(remotePort);

  // connect to socket
  try {
    std::stringstream Out;
    Out << "Connected to " << remoteIp_ << ":" << remotePort_;
    log(Out.str(), LogLevel::Info);

    socket_.connect(remoteIp_, remotePort_);
    
  } catch (SocketException &e) {
    isConnected_ = false;
    std::stringstream output;
    output << "Error connecting to " << remoteIp << " : " << remotePort_
           << ":" << e.what();
    log(output.str(), LogLevel::Error);
    return false;
  }

  isConnected_ = true;
  running_ = true;
  
  // start listening thread
  std::thread listenThread(&EthernetConnection::listenToSocket, this);
  listenThread.detach();
    
  return true;
}

bool EthernetConnection::send(uint8_t *data, size_t length) {
  try {
    socket_.send(data, length);
  } catch (SocketException &e) {
    std::stringstream output_err;
    output_err << "EthernetConnection: Error sending data: "
               << e.what();
    log(output_err.str(), LogLevel::Error);
    isConnected_ = false;
    running_ = false;
    return false;
  }

  return true;
}

void EthernetConnection::listenToSocket() {

  uint8_t buffer[incomingBufferSize_];
  size_t bytesReceived;

  while (running_) {
    try {
      // Read data from the socket
      bytesReceived = socket_.recv(buffer, incomingBufferSize_);
    } catch (SocketException &e) {
      std::stringstream output_err;
      output_err << "EthernetConnection: Error receiving data: "
                 << e.what();
      log(output_err.str(), LogLevel::Error);
      isConnected_ = false;
      running_ = false;
      return;
    }

    if (bytesReceived > 0)  {
      receivedMessage(buffer, bytesReceived);
    }
  }
  log("Multicast listening thread exiting.", LogLevel::Info);
}


}
//-----------------------------------------------------------------------------
//                                UNCLASSIFIED
//-----------------------------------------------------------------------------