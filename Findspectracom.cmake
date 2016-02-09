IF ( UNIX )
  
  FIND_PATH(spectracom_INCLUDE_DIRS 
    NAMES SpectracomGsg6.hpp
    PATHS spectracom/SpectracomGsg6.hpp
          /usr/include 
          /usr/include/spectracom
          /usr/local/spectracom 
          /usr/local/include/spectracom
          /include/spectracom )

    FIND_LIBRARY(spectracom_LIBRARIES
    NAMES spectracom
    PATHS /usr/lib
          /usr/local/lib )
    
ELSE ( UNIX )

  FIND_PATH(spectracom_INCLUDE_DIRS
    NAMES spectracom/SpectracomGsg6.hpp
    PATHS "$ENV{HOME}/local/include"
          "C:/Program Files (x86)/include" 
          "C:/Program Files/include" )
  
    FIND_LIBRARY(spectracom_LIBRARIES
      NAMES spectracom
      PATHS "$ENV{HOME}/local/lib")
  
ENDIF (UNIX)

IF ( spectracom_INCLUDE_DIRS )
  MESSAGE(STATUS "-- Looking for spectracom - found")
ELSE ( spectracom_INCLUDE_DIRS )
  MESSAGE(FATAL_ERROR "-- Looking for spectracom - not found")
ENDIF ( spectracom_INCLUDE_DIRS )

IF ( spectracom_LIBRARIES )
  MESSAGE(STATUS "-- Looking for spectracom library - found")
ELSE (spectracom_LIBRARIES)
  MESSAGE(FATAL_ERROR "-- Neither spectracom not found!")
ENDIF ( spectracom_LIBRARIES )