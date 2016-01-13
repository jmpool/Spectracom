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
  // \details Namespace containing Enumeration of all error message headings and
  //          their corresponding string values according to Spectracom
  //          protocols, and functions converting between them.
  //
  namespace errorIds {
    // \brief   Number of values in MsgIdEnum and in msgIdStringArray
    const size_t totalIds = 39;
  
    // \brief   Enum of all valid Spectracom error message IDs
    enum class MsgIds {
      NoError,
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
      RSGCommandUnderflow,
      ScenarioExecutionFailed,
      MissingScenario,
      SettingsConflict1,
      SettingsConflict2,
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
      InvalidFileType,
      UndefinedError
    };
  
    struct ErrorMsg {
      errorIds::MsgIds id;
      std::string errorString;
      
      ErrorMsg()
      : id(errorIds::MsgIds::UndefinedError),
        errorString(""){}
    };
  
    // Error Message Id strings
    const std::array<std::string, errorIds::totalIds> msgIdStringArray {
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
        "193",
        "194",
        "200",
        "220",
        "221",
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
        "1404",
        "none"
      }
    };
  
  
  
  // 0      No error
  // 100    This is the generic syntax error for devices that cannot detect more specific errors. This code indicates only that a Command Error defined in IEEE-488.2, 11.5.1.1.4 has occurred.
  // 102    An unrecognized command or data type was encountered.
  // 105    A Group Execute Trigger was received within a program message (see IEEE-488.2, 7.7).
  // 108    Parameter given for command which does not have any parameters.
  // 109    Command requiring parameter(s) is issued without them.
  // 112    Protocol keyword too long. All keywords are less than 12 characters long.
  // 113    The header is syntactically correct, but it is undefined for this specific device; for example, BXYZ is not defined for any device.
  // 120    Number format is not recognized.
  // 129    Numeric parameter value is invalid.
  // 140    This error, as well as errors 141 through –149, is generated when parsing a character data element. This particular error message is used when the device cannot detect a more specific error.
  // 141    Either the character data element contains an invalid character or the particular element received is not valid for the header.
  // 148    Character data detected when number is expected.
  // 150    String. This error as well as errors –151 through –159 is generated when parsing a string data element. This particular error message is used when the device cannot detect a more specific error.
  // 151    A string data element was expected, but was invalid for some reason (see IEEE-488.2, 7.7.5.2); for example, an END message was received before the terminal quote character.
  // 158    String data detected when number is expected.
  // 160    This error, as well as errors –161 through –169, is generated when parsing a block data element. This particular error message is used when the instrument cannot detect a more specific error.
  // 161    A block data element was expected, but was invalid for some reason (see IEEE-488.2, 7.7.6.2); for example, an END message was received before the length was satisfied.
  // 190    Command not allowed in current state.
  // 191    Command requiring scenario/signal generator executing issued when device is idle.
  // 192    Query or command for a channel that is currently not allocated to any signal.
  // 193    Too many RSG commands were received to process within a GSG 10 Hz epoch.
  // 194    Underflow detection was enabled, and no GSG RSG commands were received within a GSG 100 ms epoch.
  // 200    Scenario execution failed to start.
  // 220    Scenario/signal generator started without a scenario.
  // 221    Indicates that a legal program data element was parsed but could not be executed due to the current counter state (see IEEE-488.2, 6.4.5.3 and 11.5.1.1.5.)
  // 221    See above.
  // 222    Indicates data values are out of range or input data such as Navigation data files have incompatible ranges of validity.
  // 224    Scenario configuration has illegal coordinates or date.
  // 225    Command processing was interrupted because of the lack of memory.
  // 241    This error is given only when the reference clock signal is missing when scenario/signal generator is started or when the Ethernet MAC address cannot be found. Check that the external reference clock is connected. Verify Network Ethernet Port detection and activity lights.
  // 250    Copying/moving files is not allowed between directories.
  // 256    File operation attempted on a non existing file or directory.
  // 257    File name is empty.
  // 410    Indicates that a condition causing an INTERRUPTED Query error occurred (see IEEE-488.2, 6.3.2.3).
  // 1401   Checksum of file transferred is invalid.
  // 1403   In file transfer length is invalid. This can be happen if there is not enough memory or storage space on device to retrieve file.
  // 1404   Invalid file type given.
  
  // Full error message strings
    const std::array<std::string, errorIds::totalIds> msgStringArray {
    {
      "0,\"No error\"",
      "100,\"Command error\"",
      "102,\"Syntax error\"",
      "105,\"GET not allowed\"",
      "108,\"Parameter not allowed\"",
      "109,\"Missing parameter\"",
      "112,\"Program mnemonic too long\"",
      "113,\"Undefined header\"",
      "120,\"Numeric data error\"",
      "129,\"Numeric data out of range\"",
      "140,\"Character data error\"",
      "141,\"Invalid character data\"",
      "148,\"Character data not allowed\"",
      "150,\"String data error\"",
      "151,\"Invalid string data\"",
      "158,\"String data not allowed\"",
      "160,\"Block data error\""
      "161,\"Invalid block data\"",
      "190,\"Execution in progress\"",
      "191,\"Execution not in progress\"",
      "192,\"Unused channel\"",
      "193,\"RSG command overflow occurred\"",
      "194,\"RSG command underflow occurred\"",
      "200,\"Execution error\"",
      "220,\"Parameter error\"",
      "221,\"Settings conflict\"",
      "221,\"Settings conflict; invalid combination of channel and function\"",
      "222,\"Data out of range\"",
      "224,\"Illegal parameter value\"",
      "225,\"Out of memory\"",
      "241,\"Hardware missing\"",
      "250,\"Mass storage error\"",
      "256,\"File name not found\"",
      "257,\"File name error\"",
      "410,\"Query INTERRUPTED\"",
      "1401,\"Wrong program data checksum found\"",
      "1403,\"File length error\"",
      "1404,\"File type error\"",
      "none"
    }
  };
  
    static std::string getMessage(errorIds::MsgIds msgId) {
      return errorIds::msgStringArray[(std::size_t)msgId];
    }
  
    static std::string toString(errorIds::MsgIds inputEnum) {
      return errorIds::msgIdStringArray[(std::size_t)inputEnum];
    }
    
    static errorIds::MsgIds toEnum(std::string inputString) {
      const std::string *result = std::find(errorIds::msgIdStringArray.begin(),
                                            errorIds::msgIdStringArray.end(),
                                            inputString);
      //      if (result == stringArray.end()) {
      //        return ;
      //      } // TODO: Add exception throw for if string not valid
      
      return (errorIds::MsgIds)(std::distance(errorIds::msgIdStringArray.begin(),
                                              result)-1);
    }
  }
}

#endif /* SPECTRACOM_ERRORS_HPP */
