# Check if cmake has the required version
cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

# Set name of our project to "babymind-analysis".
project(babymind-analysis)

# INCLUDE(${CMAKE_BINARY_DIR}/Findreconstruction.cmake)
INCLUDE(${CMAKE_BINARY_DIR}/FindROOT.cmake)

#set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/MakeCalib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -std=c++11")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/lib)
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/lib)

if    (ROOT_FOUND)
  INCLUDE_DIRECTORIES(${ROOT_INCLUDE_DIR})
  LINK_DIRECTORIES   (${ROOT_LIBRARY_DIR})
endif (ROOT_FOUND)

message(STATUS "C flags      : " ${CMAKE_C_FLAGS})
message(STATUS "CXX flags    : " ${CMAKE_CXX_FLAGS})
message(STATUS "Linker flags : " ${CMAKE_EXE_LINKER_FLAGS}\n)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MakeCalib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/EvtDisp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/DataSanity)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BSDApply)

