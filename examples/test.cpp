#include "spectracom/spectracomGsg6.hpp"

void logHandler(std::string msg, LogLevel level) {
  std::cout << msg << "\n";
}

uint8_t testarray[] = {'a','a','a','a','a'};

// 192.168.10.118 5025
int main(int argc, char **argv)
{
  if(argc < 3) {
      std::cerr << "Usage: ublox_example <ip address> <port number>" << std::endl;
      return 0;
  }

  spectracom::Spectracom * device = new spectracom::Spectracom;

  device->log.connect(boost::bind(&logHandler, _1, _2));
  
  std::string ip(argv[1]);
  int port=5025;
  istringstream(argv[2]) >> port;

  // Connect to Receiver
  if (!device->connect(ip,port)) {return -1;}

  // loop forever
//  spectracom::errorIds::MsgIds errorId;
    double power;
  
  while(1) {
//      device->queryError(errorId);
    device->queryTransmitPower(power);
    usleep(1000 * 1000); // sleep for 50 ms

  }

  return 0;
}