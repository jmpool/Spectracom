cmake_minimum_required(VERSION 2.8.2)
project(spectracom)

if(${CMAKE_MAJOR_VERSION} GREATER 2)
  cmake_policy(SET CMP0042 OLD)
endif(${CMAKE_MAJOR_VERSION} GREATER 2)

# enable C++11 support
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
if (ANDROID)
  set(CMAKE_CXX_FLAGS "-std=gnu++11")
else(ANDROID)
  set(CMAKE_CXX_FLAGS "-std=c++11")
endif(ANDROID)

option(BUILD_WITH_CATKIN "Build with Catkin?" OFF)
if (DEFINED CATKIN_DEVEL_PREFIX)
  SET(BUILD_WITH_CATKIN ON)
endif(DEFINED CATKIN_DEVEL_PREFIX)

if (BUILD_WITH_CATKIN)
  message(STATUS "Building with Catkin")
  ## Find catkin macros and libraries
  # find_package(catkin REQUIRED serial)

  catkin_package(
    INCLUDE_DIRS include
    LIBRARIES spectracom
    DEPENDS Boost
  )
else(BUILD_WITH_CATKIN)
  message(STATUS "Building without Catkin")
  SET(CATKIN_PACKAGE_LIB_DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
  SET(CATKIN_PACKAGE_BIN_DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
  SET(CATKIN_GLOBAL_INCLUDE_DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")
  SET(CATKIN_PACKAGE_INCLUDE_DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")
  SET(CATKIN_DEVEL_PREFIX ${CMAKE_BINARY_DIR}/devel)
  SET(CATKIN_GLOBAL_SHARE_DESTINATION ${CMAKE_INSTALL_PREFIX}/share)
  SET(CATKIN_PACKAGE_SHARE_DESTINATION ${CATKIN_GLOBAL_SHARE_DESTINATION}/${PROJECT_NAME})

  find_package(Boost REQUIRED)
  set(catkin_LIBRARIES ${Boost_LIBRARIES})
  set(catkin_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})

endif(BUILD_WITH_CATKIN)

## System dependencies are found with CMake's conventions

###########
## Build ##
###########

# Add default source files
set(SPECTRACOM_SRCS src/spectracomGsg6.cpp
                    src/PracticalSocket.cpp
                    src/EthernetConnection.cpp)
# Add default header files
set(SPECTRACOM_HEADERS  include/spectracom/spectracomGsg6.hpp
                        include/spectracom/spectracomGsg6Protocol.hpp
                        include/spectracom/msg/Options.hpp
                        include/spectracom/msg/Commands.hpp
                        include/spectracom/msg/Queries.hpp
                        include/spectracom/PracticalSocket.h
                        include/spectracom/EthernetConnection.hpp)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include ${catkin_INCLUDE_DIRS})

## Declare a cpp library
add_library(spectracom 
            ${SPECTRACOM_SRCS}
            ${SPECTRACOM_HEADERS})

target_link_libraries(spectracom
                      ${catkin_LIBRARIES})

option(BUILD_EXAMPLES "Build examples." ON)
IF(BUILD_EXAMPLES)
# Declare a cpp executable
add_executable(spectracom_example examples/test.cpp)
target_link_libraries(spectracom_example
                      spectracom
                     ${catkin_LIBRARIES})
ENDIF(BUILD_EXAMPLES)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

# Mark executables and/or libraries for installation
install(TARGETS spectracom
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)

set(CMAKE_MODULE_PATH ${CMAKE_ROOT}/Modules)
install(FILES Findspectracom.cmake DESTINATION ${CMAKE_MODULE_PATH})