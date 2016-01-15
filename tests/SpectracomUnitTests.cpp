//------------------------------------------------------------------------------
//                                UNCLASSIFIED
//------------------------------------------------------------------------------
//===------ tests/SpectracomUnitTests.cpp - Common Definition File --------===//
//
// Copyright (C) Integrated Solutions for Systems, Inc - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief    This file contains tests for the Spectracom class.
/// \author   Chris Collins <chris.collins@is4s.com>
/// \date     January 2016
///
//===----------------------------------------------------------------------===//

#include "gtest/gtest.h"
#include "spectracom/spectracomGsg6.hpp"

using namespace spectracom;

Spectracom device_;

TEST(DeviceOptionsTest, StringArraySizeTest) {
  try {
    EXPECT_EQ(deviceOptions::totalIds, deviceOptions::stringArray.size());
  } catch(std::exception &e) {
    ADD_FAILURE() << "Caught exception : " << e.what();
  }
}

TEST(DeviceOptionsTest, EnumStringConversionsTest) {
  try {
    for (size_t i=0; i < deviceOptions::totalIds; ++i) {
      EXPECT_EQ(deviceOptions::stringArray.at(i), device_.toOptionString((deviceOptions::Enum)i));
      
      EXPECT_EQ((deviceOptions::Enum)i, device_.toOptionEnum(deviceOptions::stringArray.at(i)));
    }
  } catch(std::exception &e) {
    ADD_FAILURE() << "Caught exception : " << e.what();
  }
}

TEST(QueryIdsTest, MsgIdStringArraySizeTest) {
  try {
    EXPECT_EQ(queryIds::totalIds, queryIds::msgIdStringArray.size());
  } catch(std::exception &e) {
    ADD_FAILURE() << "Caught exception : " << e.what();
  }
}

TEST(QueryIdsTest, EnumStringConversionsTest) {
  try {
    for (uint8_t i=0; i < queryIds::totalIds; ++i) {
      EXPECT_EQ(queryIds::msgIdStringArray.at(i), device_.toQueryIdString((queryIds::MsgIds)i));
      
      EXPECT_EQ((queryIds::MsgIds)i, device_.toQueryIdEnum(queryIds::msgIdStringArray.at(i)));
    }
  } catch(std::exception &e) {
    ADD_FAILURE() << "Caught exception : " << e.what();
  }
}

TEST(ErrorIdsTest, MsgIdStringArraySizeTest) {
  try {
    EXPECT_EQ(errorIds::totalIds, errorIds::msgIdStringArray.size());
  } catch(std::exception &e) {
    ADD_FAILURE() << "Caught exception : " << e.what();
  }
}

TEST(ErrorIdsTest, EnumStringConversionsTest) {
  try {
    for (size_t i=0; i < errorIds::totalIds; ++i) {
      EXPECT_EQ(errorIds::msgIdStringArray.at(i), device_.toErrorIdString((errorIds::MsgIds)i));

      EXPECT_EQ((errorIds::MsgIds)i, device_.toErrorEnum(errorIds::msgIdStringArray.at(i)));
    }
  } catch(std::exception &e) {
    ADD_FAILURE() << "Caught exception : " << e.what();
  }
}

TEST(CommandIdsTest, MsgIdStringArraySizeTest) {
  try {
    EXPECT_EQ(commandIds::totalIds, commandIds::msgIdStringArray.size());
  } catch(std::exception &e) {
    ADD_FAILURE() << "Caught exception : " << e.what();
  }
}

TEST(CommandIdsTest, EnumStringConversionsTest) {
  try {
    for (size_t i=0; i < commandIds::totalIds; ++i) {
      EXPECT_EQ(commandIds::msgIdStringArray.at(i), device_.toCommandString((commandIds::MsgIds)i));
      
      EXPECT_EQ((commandIds::MsgIds)i, device_.toCommandEnum(commandIds::msgIdStringArray.at(i)));
    }
  } catch(std::exception &e) {
    ADD_FAILURE() << "Caught exception : " << e.what();
  }
}




int main(int argc, char **argv) {
  try {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  } catch (std::exception &e) {
    std::cerr << "Unhandled Exception: " << e.what() << std::endl;
  }
  return 1;
}
//------------------------------------------------------------------------------
//                                UNCLASSIFIED
//------------------------------------------------------------------------------