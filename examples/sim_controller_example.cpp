#include "spectracom/spectracomGsg6.hpp"

// 192.168.10.118 5025
int main(int argc, char **argv)
{
  if(argc < 3) {
      std::cerr << "Usage: sim_controller_example <ip address> <port number>" << std::endl;
      return 0;
  }

  spectracom::Spectracom * device = new spectracom::Spectracom;
  
  std::string ip(argv[1]);
  int port=5025;
  istringstream(argv[2]) >> port;

  // Connect to Receiver
  if (!device->connect(ip,port)) {return -1;}
  
  // Pick scenario
  device->commandLoadScenario("IS4S_ROOF-l1.scen");
  // Set Parameters
  device->commandTransmitPower(-130);
  device->commandCarrierToNoise(50);
  // Start scenario
  device->commandStartScenario();

  return 0;
}