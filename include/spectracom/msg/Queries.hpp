///-----------------------------------------------------------------------------
///                                UNCLASSIFIED
///-----------------------------------------------------------------------------
///==----------------------- spectracomGsg6/Queries.hpp --------------------==//
///
/// Copyright (C) Integrated Solutions for Systems, Inc - All Rights Reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited.
/// Proprietary and confidential.
///
///===---------------------------------------------------------------------===//
///
/// \file
/// \brief    Spectracom Query message IDs
/// \author   Chris Collins <chris.collins@is4s.com>
/// \date     January 2016
///
///===---------------------------------------------------------------------===//

#ifndef SPECTRACOM_QUERIES_HPP
#define SPECTRACOM_QUERIES_HPP

#include <string>
#include <array>

namespace spectracom {
  
  // \brief  Spectracom Query messages
  //
  // \details Namespace containing Enumeration of all query message headings and
  //          their corresponding string values according to Spectracom
  //          protocols, and functions converting between them.
  //
  namespace queryIds {
    
    // \brief   Number of values in MsgIdEnum and in msgIdStringArray
    const size_t totalIds = 74;
    
    // \brief   Char on end of MsgId to indicate it's a query
    const char queryIndicator = '?';
      
    // \brief   Enum of all valid Spectracom query message IDs
    enum class MsgIds {
      /// Common
      Common_EventStatusEnable,
      Common_EventStatusRegister,
      Common_Identification,
      Common_OperationComplete,
      Common_ServiceRequestEnable,
      Common_StatusByteQuery,
      Common_SelfTest,
      Common_WaitToContinue,
      /// System
      System_Error,
      /// Source
      Source_TransmitPower,
      Source_ExternalReferenceSignal,
      Source_PpsOutput,
      Source_ExternalAttenuation,
      Source_Noise_Control,
      Source_Noise_Cno,
      Source_Noise_Bandwidth,
      Source_Noise_Offset,
      Source_Channel_Control,
      Source_Channel_SatelliteIdentifier,
      Source_Channel_StartTime,
      Source_Channel_Ephemeris,
      Source_Channel_Frequency,
      Source_Channel_SignalType,
      Source_Scenario_Load,
      Source_Scenario_Control,
      Source_Scenario_PropagationEnvironmentModel,
      Source_Scenario_Log,
      Source_Scenario_Observations,
      Source_Scenario_LogNavDataToRinex,
      Source_Scenario_SatelliteId,          // [n]
      Source_Signal_SignalType,             // [n]
      Source_Scenario_Frequency,            // [n]
      Source_Scenario_ChannelPower,         // [n]
      Source_Scenario_SvModel,              // [n]
      Source_Scenario_ListModels,
      Source_Scenario_AntennaModel,
      Source_Scenario_TroposphericModel,
      Source_Scenario_IonosphericModel,
      Source_Scenario_KeepAltitude,
      Source_Scenario_Position,
      Source_Scenario_Ecef_Position,
      Source_Scenario_RtcmMessages,
      Source_Scenario_RtcmConfig,
      Source_Scenario_DuplicateSv,
      Source_Scenario_Multipath,            // [n]
      Source_Keylock_Password,
      Source_Keylock_Status,
      /// TODO: Mass Memory Commands
      /// TODO: Sensors Commands
      Source_Scenario_SpeedOverGround,
      Source_Scenario_Heading,
      Source_Scenario_HeadingRate,
      Source_Scenario_TurnRate,
      Source_Scenario_TurnRadius,
      Source_Scenario_VelocityOverGround,
      Source_Scenario_VerticalSpeed,
      Source_Scenario_EnuVelocity,
      Source_Scenario_EcefVelocity,
      Source_Scenario_Acceleration,
      Source_Scenario_VerticalAcceleration,
      Source_Scenario_EnuAcceleration,
      Source_Scenario_EcefAcceleration,
      Source_Scenario_AttitudeRadians,
      Source_Scenario_AttitudeDegrees,
      Source_Scenario_AttitudeRateRadians,
      Source_Scenario_AttitudeRateDegrees,
      Source_Scenario_KeplerOrbitParameters,
      Source_Scenario_Runtime,
      Source_Scenario_Datetime,
      Source_Scenario_ElapsedTime,
      Source_Scenario_UnderflowDetection,
      Source_Scenario_Doppler,
      Source_Scenario_SvRange,
      Source_Scenario_ChannelInView,
      Source_Scenario_SvInView,
      Source_Scenario_SvPosition           // [n]
    };
      
    const std::array<std::string, totalIds> msgIdStringArray = {
      {
        "*ESE",
        "*ESR",
        "*IDN",
        "*OPC",
        "*SRE",
        "*STB",
        "*TST",
        "*WAI",
        "SYSTEM:ERROR",
        "SOURCE:POWER",
        "SOURCE:EXTREF",
        "SOURCE:PPSOUTPUT",
        "SOURCE:EXTATT",
        "SOURCE:NOISE:CONTROL",
        "SOURCE:NOISE:CNO",
        "SOURCE:NOISE:BW",
        "SOURCE:NOISE:OFFSET",
        "SOURCE:ONECHN:CONTROL",
        "SOURCE:ONECHN:SATID",
        "SOURCE:ONECHN:STARTTIME",
        "SOURCE:ONECHN:EPHEMERIS",
        "SOURCE:ONECHN:FREQUENCY",
        "SOURCE:ONECHN:SIGNALTYPE",
        "SOURCE:SCENARIO:LOAD",
        "SOURCE:SCENARIO:CONTROL",
        "SOURCE:SCENARIO:PROPENV",
        "SOURCE:SCENARIO:LOG",
        "SOURCE:SCENARIO:OBSERVATION",
        "SOURCE:SCENARIO:NAV",
        "SOURCE:SCENARIO:SATID",      // [n]
        "SOURCE:SCENARIO:SIGNALTYPE", // [n]
        "SOURCE:SCENARIO:FREQUENCY",  // [n]
        "SOURCE:SCENARIO:POWER",      // [n]
        "SOURCE:SCENARIO:SVMODEL",    // [n]
        "SOURCE:SCENARIO:LIST",
        "SOURCE:SCENARIO:ANTENNAMODEL",
        "SOURCE:SCENARIO:TROPOMODEL",
        "SOURCE:SCENARIO:IONOMODEL",
        "SOURCE:SCENARIO:KEEPALTITUDE",
        "SOURCE:SCENARIO:POSITION",
        "SOURCE:SCENARIO:ECEFPOSITION",
        "SOURCE:SCENARIO:RTCM",
        "SOURCE:SCENARIO:RTCMCFG",
        "SOURCE:SCENARIO:DUPLICATE",
        "SOURCE:SCENARIO:MULTIPATH",  // [n]
        "SOURCE:KEYLOCK:PASSWORD",
        "SOURCE:KEYLOCK:STATUS",
        /// TODO: Mass Memory Commands
        /// TODO: Sensors Commands
        "SOURCE:SCENARIO:SPEED",
        "SOURCE:SCENARIO:HEADING",
        "SOURCE:SCENARIO:RATEHEADING",
        "SOURCE:SCENARIO:TURNRATE",
        "SOURCE:SCENARIO:TURNRADIUS",
        "SOURCE:SCENARIO:VELOCITY",
        "SOURCE:SCENARIO:VSPEED",
        "SOURCE:SCENARIO:ENUVELOCITY",
        "SOURCE:SCENARIO:ECEFVELOCITY",
        "SOURCE:SCENARIO:ACCELERATION",
        "SOURCE:SCENARIO:VACCEL",
        "SOURCE:SCENARIO:ENUACCEL",
        "SOURCE:SCENARIO:ECEFACCEL",
        "SOURCE:SCENARIO:PRYATTITUDE",
        "SOURCE:SCENARIO:DPRYATTITUDE",
        "SOURCE:SCENARIO:PRYRATE",
        "SOURCE:SCENARIO:DPRYRATE",
        "SOURCE:SCENARIO:KEPLER",
        "SOURCE:SCENARIO:RUNTIME",
        "SOURCE:SCENARIO:DATETIME",
        "SOURCE:SCENARIO:ELAPSEDTIME",
        "SOURCE:SCENARIO:RSGUNDERFLOW",
        "SOURCE:SCENARIO:DOPPLER",
        "SOURCE:SCENARIO:PRANGE",
        "SOURCE:SCENARIO:CHINVIEW",
        "SOURCE:SCENARIO:SVINVIEW",
        "SOURCE:SCENARIO:SVPOS"       // [n]
      }
    };
  }
}
#endif // SPECTRACOM_QUERIES_HPP