#include "spectracom/SpectracomGsg6.hpp"

// 192.168.10.118 5025
int main(int argc, char **argv)
{
  if(argc < 4) {
      std::cerr << "Usage: set_simulator_cno <ip address> <port number> <C/No (dB-Hz)>" << std::endl;
      return 0;
  }

  spectracom::Spectracom * device = new spectracom::Spectracom;
  
  device->log_.connect(boost::bind(&logutils::printLogToStdOut, _1, _2));
                       
  std::string ip(argv[1]);
  int port=5025;
  istringstream(argv[2]) >> port;

  // Connect to Receiver
  if (!device->connect(ip,port)) {return -1;}
  
  double cno = 50.0;
  istringstream(argv[3]) >> cno;
  
  device->commandCarrierToNoise(cno);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  }

  return 0;
}
