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

//#include <string>
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
    bool connect(std::string remoteIp, uint16_t remotePort);

    // \brief  Sends data to simulator
    bool send(std::string data);


    // -------------------------------------------------
    // Queries
    
    // \brief [*IDN?] Simulator Identification Query
    bool queryIdentification();
    
    // -------------------------------------------------
    // Commands
    
    
    // \brief  Signal generated for log message occurance
    bs2::signal<void(const std::string &, const LogLevel &)> log;
    
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
    
    Queries query_;
  };
}

#endif