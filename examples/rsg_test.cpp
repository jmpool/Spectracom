#include "spectracom/SpectracomGsg6.hpp"
#include <string>
#include <stdlib.h>

spectracom::Spectracom * device = new spectracom::Spectracom;

bool startScenario(string scenarioName)
{
  cout<<"Entered startScenario"<<endl;
  bool startStatus;
  device->commandLoadScenario("WoltoszStatic.scen");
  // Set Parameters
  device->commandTransmitPower(-130);
  device->commandCarrierToNoise(50);
  // Start scenario
  device->commandStartScenario();
  return true;
}

bool waitForScenarioToStart()
{
  cout<<"Entered waitForScenarioToStart"<<endl;
  string queryString = "SOUR:SCEN:CONT";
  string responseString = "nothing";
  string started = "START\n";

  while(responseString.compare(started) != 0)
  {
    sleep(1);
    device->query(queryString, responseString);
    // cout<<"Got query response: "<<responseString;
  }
  
  cout<<"Scenario started successfully!"<<endl;
  return true;
}



bool sendRsgCommand()
{
  string rsgCommand = "SOUR:SCEN:ECEFPOS IMM,1000.0,2000.0,3000.0";
  device->send(rsgCommand);
  device->commandWaitToContinue();
  cout<<"Sent: "<<rsgCommand<<endl;
  return true;
}



bool queryPosition()
{
  string queryString = "SOUR:SCEN:ECEFPOS";
  string responseString;
  device->query(queryString, responseString);
  cout<<"Received: "<<responseString;
  return true;
}


int main(int argc, char **argv)
{
  string scenarioName = "WoltoszStatic.scen";
  int port=5025;

  if(argc < 3) {
      std::cerr << "Usage: sim_controller_example <ip address> <port number>" << std::endl;
      return 0;
  }

  // spectracom::Spectracom * device = new spectracom::Spectracom;
  
  std::string ip(argv[1]);
  istringstream(argv[2]) >> port;

  // Connect to Receiver
  if (!device->connect(ip,port)) {return -1;}
  
  startScenario(scenarioName);
  cout<<"Exited startScenario"<<endl;
  waitForScenarioToStart();
  sendRsgCommand();
  queryPosition();
  return 0;
}
