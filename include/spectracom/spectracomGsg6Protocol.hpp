//-----------------------------------------------------------------------------
//                                UNCLASSIFIED
//-----------------------------------------------------------------------------
//==---------------- spectracomGsg6/spectracomGsg6Protocol.hpp ------------==//
// 
// Copyright (C) Integrated Solutions for Systems, Inc - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited. 
// Proprietary and confidential. 
//
//===---------------------------------------------------------------------===//
/// 
/// \file 
/// \brief    
/// \details  
/// 
/// \author   Chris Collins <chris.collins@is4s.com> 
/// \date     January 2016 
///
//===---------------------------------------------------------------------===//

#ifndef SPECTRACOM_GSG6_PROTOCOL_HPP
#define SPECTRACOM_GSG6_PROTOCOL_HPP

#include <string>

#include "spectracom/msg/Options.hpp"
#include "spectracom/msg/Commands.hpp"
#include "spectracom/msg/Queries.hpp"
#include "spectracom/msg/Errors.hpp"

namespace spectracom {

  const char commaDelimiter = ',';
  const char whitespaceDelimiter = ' ';
  const char endlineIndicator = '\n';
  const char protocolErrorStartChar = '-';
  
  /// \brief  Enables Event Status Bits Register
  /// \details  Used in command '*ESE', '*ESE?', '*ESR?'
  enum class EventStatusEnableRegister {
    PowerOnOccured        = 0b10000000,
    UserRequest           = 0b01000000,
    CommandError          = 0b00100000,
    ExecutionError        = 0b00010000,
    DeviceDependentError  = 0b00001000,
    QueryError            = 0b00000100,
    RequestControl        = 0b00000010, // NOT USED
    OperationComplete     = 0b00000001
  };

  /// \brief  
  enum class ServiceRequestEnableRegister {
    OperationStatus           = 0b10000000,
    RequestService            = 0b01000000,
    EventStatusBit            = 0b00100000,
    MessageAvailable          = 0b00010000,  
    QuestionableSignalStatus  = 0b00001000,
    ErrorAvailable            = 0b00000100,
    NotUsed                   = 0b00000010,
    DeviceStatus              = 0b00000001,
  };

  enum class StatusByteRegister {
    EnabledStatusHasOccured               = 0b10000000,
    ReasonForRequestingService            = 0b01000000,
    EnabledStatusEventConditionHasOccured = 0b00100000,
    OutputMessageReady                    = 0b00010000,
    QuestionableOutputSignal              = 0b00001000,
    ErrorAvailable                        = 0b00000100
  };
  
  enum class ProtocolErrorIds {
    UnrecognizedError = 0,
    GenericCommandError = 100,
    SyntaxError = 102,
    GroupExecuteTriggerNotAllowed = 105,
    ParameterNotAllowed = 108,
    MissingParameter = 109,
    ProgramKeywordTooLong = 112,
    UndefinedHeader = 113,
    NumericDataError = 120,
    NumericDataOutOfRange = 129,
    GenericCharDataError = 140,
    InvalidCharData = 141,
    NumericNotCharDataExpected = 148,
    GenericStringDataError = 150,
    InvalidStringData = 151,
    NumberNotStringDataExpected = 158,
    GenericBlockDataError = 160,
    InvalidBlockData = 161,
    ExecutionInProgress = 190,
    ExecutionNotInProgress = 191,
    UnusedChannel = 192,
    RsgCommandOverflow = 194,
    ScenarioExecutionFailed = 200,
    MissingScenario = 220,
    SettingsConflict = 221,
    DataOutOfRange = 222,
    IllegalCoordinateOrDate = 224,
    OutOfMemory = 225,
    HardwareMissing = 241,
    MassStorageError = 250,
    FileNotFound = 256,
    FileNameEmpty = 257,
    QueryInterupted = 410,
    InvalidChecksum = 1401,
    FileTransferLengthInvalid = 1403,
    InvalidFileType = 1404,
  };

}
#endif  // SPECTRACOM_GSG6_PROTOCOL_HPP