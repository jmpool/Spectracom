///-----------------------------------------------------------------------------
///                                UNCLASSIFIED
///-----------------------------------------------------------------------------
///==----------------------- spectracomGsg6/Options.hpp --------------------==//
///
/// Copyright (C) Integrated Solutions for Systems, Inc - All Rights Reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited.
/// Proprietary and confidential.
///
///===---------------------------------------------------------------------===//
///
/// \file
/// \brief    Spectracom Device Options 
/// \author   Chris Collins <chris.collins@is4s.com>
/// \date     January 2016
///
///===---------------------------------------------------------------------===//

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
  }
}
#endif // SPECTRACOM_OPTIONS_HPP