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

  // \brief   Spectracom device Options
  //
  // \details Namespace containing Device options. Available options are
  //          returned in response to query '*IDN?'. Contains enum and string
  //          forms of the options and functions to convert between.
  namespace deviceOptions {
    // \brief   Number of values in MsgIdEnum and in msgIdStringArray
    const size_t totalIds = 24;
    
    // \brief   Enum of all valid device options
    enum class Enum {
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
    
    const std::array<std::string, deviceOptions::totalIds> stringArray {
      {
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
      }
    };
    
    static std::string toString(deviceOptions::Enum inputEnum) {
      return deviceOptions::stringArray[(std::size_t)inputEnum];
    }
    
    static deviceOptions::Enum toEnum(std::string inputString) {
      const std::string *result = std::find(deviceOptions::stringArray.begin(),
                                            deviceOptions::stringArray.end(),
                                            inputString);
      //      if (result == stringArray.end()) {
      //        return ;
      //      } // TODO: Add exception throw for if string not valid
      
      return (deviceOptions::Enum)( std::distance(
                                    deviceOptions::stringArray.begin(),
                                    result)-1);
    }
  }
}
#endif // SPECTRACOM_OPTIONS_HPP
