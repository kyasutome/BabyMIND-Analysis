# Install script for directory: /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/MakeCalib/cmake_install.cmake")
  include("/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/EvtDisp/cmake_install.cmake")
  include("/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/DataSanity/cmake_install.cmake")
  include("/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/BSDApply/cmake_install.cmake")
  include("/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/YASUTracker/cmake_install.cmake")
  include("/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/Recon/cmake_install.cmake")
  include("/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/DataQuality/cmake_install.cmake")
  include("/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/MakeEvent/cmake_install.cmake")
  include("/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/DetPerform/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
