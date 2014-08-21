# Copyright: (C) 2014 Walkman Consortium
# Authors: Edoardo Farnioli, Enrico Mingo, Alessio Rocchi
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 2.8.11)
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 OLD)
    cmake_policy(SET CMP0005 NEW)
endif(COMMAND cmake_policy)
include(ExternalProject)

project(LocoMan)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

FIND_PACKAGE(YARP REQUIRED)
FIND_PACKAGE(iDynTree REQUIRED)
FIND_PACKAGE(kdl_codyco REQUIRED)
FIND_PACKAGE(orocos_kdl REQUIRED)
FIND_PACKAGE(srdfdom REQUIRED)
FIND_PACKAGE(urdf REQUIRED)
FIND_PACKAGE(rosconsole REQUIRED)
FIND_PACKAGE(kdl_parser REQUIRED)
FIND_PACKAGE(moveit_core REQUIRED)
FIND_PACKAGE(tf REQUIRED)
FIND_PACKAGE(Eigen3 REQUIRED)
FIND_PACKAGE(drc_shared REQUIRED)
FIND_PACKAGE(PCL 1.2 REQUIRED)

set(VARS_PREFIX "LOCOMAN")
                            
find_package(YCM REQUIRED)
include(YCMDefaultDirs)
ycm_default_dirs(${VARS_PREFIX})


############### ENABLING TESTING #######################
enable_testing()

#finding GTest
#FIND_PACKAGE(GTest REQUIRED)
set(gTestSource "/usr/src/gtest")
ExternalProject_Add(GTest-ext SOURCE_DIR ${gTestSource}
                              PREFIX "${CMAKE_CURRENT_BINARY_DIR}/external"
                              INSTALL_COMMAND "")
set(GTEST_LIB_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/src/GTest-ext-build/")
set(GTEST_INCLUDE_DIRS ${gTestSource})
set(GTEST_BOTH_LIBRARIES gtest gtest_main)
########################################################

# add include directories
INCLUDE_DIRECTORIES(include ${YARP_INCLUDE_DIRS} ${iDynTree_INCLUDE_DIRS} 
                            ${paramHelp_INCLUDE_DIRS}
                            ${kdl_codyco_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} 
                            ${PCL_INCLUDE_DIRS}
                            ${GTEST_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTEST_LIB_DIRS})

ADD_DEFINITIONS(${PCL_DEFINITIONS})

# add required linker flags
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ICUB_LINK_FLAGS}")

# for every file in drc_INCLUDES CMake already sets the property HEADER_FILE_ONLY
file(GLOB_RECURSE locoman_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include" *.h)

## Declare drc_shared library
add_library(locoman SHARED
  src/CFLMM.cpp
  ${locoman_INCLUDES}
)

TARGET_LINK_LIBRARIES(locoman ${drc_shared_LIBRARIES} ${iDynTree_LIBRARIES} ${YARP_LIBRARIES})

ADD_EXECUTABLE(testCFLMM src/tests/TestCFLMM.cpp)
TARGET_LINK_LIBRARIES(testCFLMM ${GTEST_BOTH_LIBRARIES} pthread
                                ${drc_shared_LIBRARIES} ${iDynTree_LIBRARIES} ${YARP_LIBRARIES}
                                locoman)
add_dependencies(testCFLMM GTest-ext locoman)

add_test(locoman_test_CFLMM bin/testCFLMM)

target_include_directories(locoman PUBLIC "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>"
                                               "$<INSTALL_INTERFACE:${${VARS_PREFIX}_INSTALL_INCLUDEDIR}>")
                   
install(TARGETS locoman  
        EXPORT  locoMan
        ARCHIVE DESTINATION "${${VARS_PREFIX}_INSTALL_BINDIR}" COMPONENT lib
        RUNTIME DESTINATION "${${VARS_PREFIX}_INSTALL_BINDIR}" COMPONENT bin
        LIBRARY DESTINATION "${${VARS_PREFIX}_INSTALL_LIBDIR}" COMPONENT shlib
        PUBLIC_HEADER DESTINATION "${${VARS_PREFIX}_INSTALL_INCLUDEDIR}/LocoMan" COMPONENT dev)

        
set_property(GLOBAL APPEND PROPERTY ${VARS_PREFIX}_TARGETS locoman)


include(InstallBasicPackageFiles)

install_basic_package_files(locoMan VARS_PREFIX ${VARS_PREFIX}
                                    VERSION "1.0.0"
                                    TARGETS_PROPERTY ${VARS_PREFIX}_TARGETS
                                    COMPATIBILITY SameMajorVersion

)

include(AddUninstallTarget)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CMAKE_INSTALL_PREFIX_PATH}/include
)

add_custom_target(  locoman_test ALL
                    COMMAND ${CMAKE_CTEST_COMMAND}
                    DEPENDS locoman testCFLMM)
