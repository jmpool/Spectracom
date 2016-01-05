//-----------------------------------------------------------------------------
//                                UNCLASSIFIED
//-----------------------------------------------------------------------------
//==------------------- spectracomGsg6/spectracomGsg6.hpp ------------------==//
//
// Copyright (C) Integrated Solutions for Systems, Inc - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
//===---------------------------------------------------------------------===//
///
/// \file
/// \brief
/// \details
///
/// \author   Chris Collins <chris.collins@is4s.com>
/// \date     January 2016
///
//===---------------------------------------------------------------------===//

#ifndef SPECTRACOM_GSG6_HPP
#define SPECTRACOM_GSG6_HPP

#include <string>
#include <iostream>

//#include <functional>
//#include <boost/signals2.hpp>

#include "spectracom/EthernetConnection.hpp"
#include "spectracom/spectracomGsg6Protocol.hpp"

namespace spectracom {


  class Spectracom {
  public:
    Spectracom() {};
    ~Spectracom(){};
    
    // \brief   Opens connection to simulator
    bool connect(std::string remoteIp, uint16_t remotePort) {

      // Connect boost signal 
      connection_.receivedMessage.connect(boost::bind(&Spectracom::bufferIncomingData, this, _1, _2));

      // Create TCP connection
      return connection_.connect(remoteIp, remotePort);
    };

    // \brief  Sends data to simulator
    bool send(std::string data) {
      return connection_.send(data);
    };


    /// Common Commands
    // \brief [*IDN?] Simulator Identification Query
    bool queryIdentification();
    
  private:
    
    void bufferIncomingData(uint8_t *message, size_t length) {
      std::stringstream out;
      for (size_t i=0; i < length; ++i) {
        out << message[i];
      }
      std::cout << out.str() << std::endl;
    };

    void parseMessage(uint8_t *message, size_t length);

    // EthernetConnection object
    EthernetConnection connection_;
    
  };
}

#endif