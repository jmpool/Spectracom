///-----------------------------------------------------------------------------
///                                UNCLASSIFIED
///-----------------------------------------------------------------------------
///==------------ spectracomGsg6/SpectracomErrorException.hpp --------------==//
///
/// Copyright (C) Integrated Solutions for Systems, Inc - All Rights Reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited.
/// Proprietary and confidential.
///
///===---------------------------------------------------------------------===//
///
/// \file
/// \brief    Exception for Spectracom reported errors
/// \author   Chris Collins <chris.collins@is4s.com>
/// \date     January 2016
///
///===---------------------------------------------------------------------===//

#ifndef SPECTRACOM_ERROR_EXCEPTION_HPP
#define SPECTRACOM_ERROR_EXCEPTION_HPP

#include <iostream>
#include <exception>

using namespace std;

namespace spectracom {
  class SpectracomErrorException: public exception
  {
  public:
    SpectracomErrorException(std::string &errorMessage)
    : errorMessage_(header+errorMessage){}
    
    const char* what() const throw() {return errorMessage_.c_str();};
  private:
    const std::string header = "Spectracom Device returned Error # ";
    const std::string errorMessage_;
  };
}
#endif /* SPECTRACOM_ERROR_EXCEPTION_HPP */
