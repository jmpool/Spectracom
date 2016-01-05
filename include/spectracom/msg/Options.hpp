//
//  Options.hpp
//  spectracom
//
//  Created by collinsc on 1/4/16.
//
//

#include <string>
#include <array>
#include <algorithm>

#ifndef SPECTRACOM_OPTIONS_HPP
#define SPECTRACOM_OPTIONS_HPP

namespace spectracom {
    
  /// /brief  Available optional capabilities of connected simulator
  /// /details
  class Options {
  public:
    enum class MsgEnum : std::size_t {
      Sbas,
      Trajectories,
      FixedBandwidthNoise,
      VariableBandwidthNoise,
      InterferenceChannels,
      Multipath,
      SimulateNow,
      Pps,
      HighVelocityAltitudeExtendedLimits,
      L2andPcode,
      L2c,
      L5,
      L6,
      VirtualBasestationPlusRtcm,
      Galileo,
      Glonass,
      RealTimeScenarioGeneration,
      Beidou,
      RecordPlayback,
      Jamming,
      SensorSimulation,
      Qzss,
      VisibilityTerrainObscuration,
      IrnssL5
    };
    
    std::array<std::string, 24> stringArray {
      "SBAS",
      "TRAJ",
      "FN",
      "VN",
      "INTF",
      "MP",
      "NOW",
      "PPS",
      "HV",
      "L2",
      "L2C",
      "L5",
      "L6",
      "RTK",
      "GAL",
      "GLO",
      "RSG",
      "BDS",
      "RP",
      "JAM",
      "SEN",
      "QZ",
      "VIS",
      "IRN"
    };
    
    std::string toString(const MsgEnum &inputEnum) {
      return stringArray[(std::size_t)inputEnum];
    }
    
    MsgEnum toMsgEnum(const std::string &inputString) {
      std::string *result = std::find(stringArray.begin(), stringArray.end(), inputString);
      
      //      if (result == stringArray.end()) {
      //        return ;
      //      } // TODO: Add exception throw for if string not valid
      
      return (MsgEnum)(std::distance(stringArray.begin(), result)-1);
    }
  };

}
#endif // SPECTRACOM_OPTIONS_HPP
