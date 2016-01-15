///-----------------------------------------------------------------------------
///                                UNCLASSIFIED
///-----------------------------------------------------------------------------
///==------------------- spectracomGsg6/ConnectionException ----------------==//
///
/// Copyright (C) Integrated Solutions for Systems, Inc - All Rights Reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited.
/// Proprietary and confidential.
///
///===---------------------------------------------------------------------===//
///
/// \file
/// \brief    Exception thrown when connection to device fails
/// \author   Chris Collins <chris.collins@is4s.com>
/// \date     January 2016
///
///===---------------------------------------------------------------------===//

#ifndef CONNECTION_EXCEPTION_HPP
#define CONNECTION_EXCEPTION_HPP

#include <iostream>
#include <exception>

using namespace std;

namespace spectracom {
  class ConnectionException: public exception
  {
    virtual const char* what() const throw()
    {
      return "Lost connection to device.";
    }
  };
}
#endif /* CONNECTION_EXCEPTION_HPP */
