//
//  Errors.hpp
//  spectracom
//
//  Created by collinsc on 1/7/16.
//
//

#ifndef SPECTRACOM_ERRORS_HPP
#define SPECTRACOM_ERRORS_HPP

#include <string>
#include <array>
//#include <algorithm>

namespace spectracom {
  // \brief  Spectracom Command messages
  //
  // \details Class containing Enumeration of all error message headings and
  //          their corresponding string values according to Spectracom
  //          protocols, and functions converting between them.
  //
  class Errors {
  public:
    // \brief   Number of values in MsgIdEnum and in msgIdStringArray
    static const size_t totalErrors = 66;
    
    // \brief   Error message start char
    static const char errorIndicator = '-';
    
    // \brief   Enum of all valid Spectracom error message IDs
    enum class MsgIds {
      UnrecognizedError,
      GenericCommandError,
      SyntaxError,
      GroupExecuteTriggerNotAllowed,
      ParameterNotAllowed,
      MissingParameter,
      ProgramKeywordTooLong,
      UndefinedHeader,
      NumericDataError,
      NumericDataOutOfRange,
      GenericCharDataError,
      InvalidCharData,
      NumericNotCharDataExpected,
      GenericStringDataError,
      InvalidStringData,
      NumberNotStringDataExpected,
      GenericBlockDataError,
      InvalidBlockData,
      ExecutionInProgress,
      ExecutionNotInProgress,
      UnusedChannel,
      RsgCommandOverflow,
      ScenarioExecutionFailed,
      MissingScenario,
      SettingsConflict,
      DataOutOfRange,
      IllegalCoordinateOrDate,
      OutOfMemory,
      HardwareMissing,
      MassStorageError,
      FileNotFound,
      FileNameEmpty,
      QueryInterupted,
      InvalidChecksum,
      FileTransferLengthInvalid,
      InvalidFileType
    };
    
    const std::array<std::string, totalErrors> msgIdStringArray {
      {
        "0",
        "100",
        "102",
        "105",
        "108",
        "109",
        "112",
        "113",
        "120",
        "129",
        "140",
        "141",
        "148",
        "150",
        "151",
        "158",
        "160",
        "161",
        "190",
        "191",
        "192",
        "194",
        "200",
        "220",
        "221",
        "222",
        "224",
        "225",
        "241",
        "250",
        "256",
        "257",
        "410",
        "1401",
        "1403",
        "1404"
      }
    };
    
    std::string toString(MsgIds inputEnum) {
      return msgIdStringArray[(std::size_t)inputEnum];
    }
    
    MsgIds toEnum(std::string inputString) {
      const std::string *result = std::find(msgIdStringArray.begin(),
                                            msgIdStringArray.end(),
                                            inputString);
      //      if (result == stringArray.end()) {
      //        return ;
      //      } // TODO: Add exception throw for if string not valid
      
      return (MsgIds)(std::distance(msgIdStringArray.begin(), result)-1);
    }
  };
}

#endif /* SPECTRACOM_ERRORS_HPP */
