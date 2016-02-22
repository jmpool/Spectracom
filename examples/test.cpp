#include "spectracom/SpectracomGsg6.hpp"

// 192.168.10.118 5025
int main(int argc, char **argv)
{
  if(argc < 3) {
      std::cerr << "Usage: spectracom_example <ip address> <port number>" << std::endl;
      return 0;
  }

  spectracom::Spectracom * device = new spectracom::Spectracom;
  
  device->log_.connect(boost::bind(&logutils::printLogToStdOut, _1, _2));
                       
  std::string ip(argv[1]);
  int port=5025;
  istringstream(argv[2]) >> port;

  // Connect to Receiver
  if (!device->connect(ip,port)) {return -1;}

  // loop forever
//    double power;
  
  while(1) {
      device->queryError();
//    device->queryTransmitPower(power);
    usleep(1000 * 1000); // sleep for 50 ms

  }

  return 0;
}
