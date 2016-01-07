#include "spectracom/spectracomGsg6.hpp"


int main(int argc, char **argv)
{
    if(argc < 3) {
        std::cerr << "Usage: ublox_example <ip address> <port number>" << std::endl;
        return 0;
    }

    spectracom::Spectracom * device = new spectracom::Spectracom;

    
    std::string ip(argv[1]);
    int port=5025;
    istringstream(argv[2]) >> port;

    // Connect to Receiver
//    bool result = device->connect(ip,port);
//    if (result) {
//        cout << "Successfully connected." << endl;
//    }
//    else {
//        cout << "Failed to connect." << endl;
//        return -1;
//    }

    // loop forever
    while(1) {
      device->send("*TST?\n");
      usleep(100 * 1000); // sleep for 50 ms

    }

    return 0;
}