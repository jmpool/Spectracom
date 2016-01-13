//
//  ConnectionException.hpp
//  spectracom
//
//  Created by collinsc on 1/13/16.
//
//

#ifndef CONNECTION_EXCEPTION_HPP
#define CONNECTION_EXCEPTION_HPP

#include <iostream>
#include <exception>

using namespace std;

class ConnectionException: public exception
{
  virtual const char* what() const throw()
  {
    return "Lost connection to device.";
  }
};



#endif /* CONNECTION_EXCEPTION_HPP */
