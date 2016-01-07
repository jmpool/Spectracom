#include "spectracom/spectracomGsg6.hpp"

namespace spectracom {
  
  bool Spectracom::connect(std::string remoteIp, uint16_t remotePort) {
    
    // Connect boost signal
    connection_.receivedMessage.connect(boost::bind(&Spectracom::bufferIncomingData, this, _1, _2));
    
    // Create TCP connection
    return connection_.connect(remoteIp, remotePort);
  };
  
  bool Spectracom::send(std::string data) {
    return connection_.send(data);
    return true;
  };
  

  // -------------------------------------------------
  // Queries
  
  bool Spectracom::queryIdentification() {
    try {
      
      std::string str = query_.toString(Queries::MsgIds::Common_Identification)
                        + Queries::queryIndicator + endlineIndicator;
      return send(str);
    } catch (std::exception &e) {
      std::stringstream error;
      error << "Error in Spectracom::queryIdentification(): " << e.what();
      log(error.str(), LogLevel::Error);
      return false;
    }
  };
  
  
  
}
