# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/DataQualityCheck.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/DataQualityCheck.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/DataQualityCheck.dir/flags.make

examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o: examples/CMakeFiles/DataQualityCheck.dir/flags.make
examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o: ../examples/babyMindDataQualityCheck.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o"
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples && /Applications/Xcode9.1.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o -c /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/examples/babyMindDataQualityCheck.cpp

examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.i"
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples && /Applications/Xcode9.1.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/examples/babyMindDataQualityCheck.cpp > CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.i

examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.s"
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples && /Applications/Xcode9.1.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/examples/babyMindDataQualityCheck.cpp -o CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.s

examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o.requires:

.PHONY : examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o.requires

examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o.provides: examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/DataQualityCheck.dir/build.make examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o.provides.build
.PHONY : examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o.provides

examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o.provides.build: examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o


# Object files for target DataQualityCheck
DataQualityCheck_OBJECTS = \
"CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o"

# External object files for target DataQualityCheck
DataQualityCheck_EXTERNAL_OBJECTS =

../bin/DataQualityCheck: examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o
../bin/DataQualityCheck: examples/CMakeFiles/DataQualityCheck.dir/build.make
../bin/DataQualityCheck: ../lib/libBabyMINDUnpack.dylib
../bin/DataQualityCheck: examples/CMakeFiles/DataQualityCheck.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/DataQualityCheck"
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DataQualityCheck.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/DataQualityCheck.dir/build: ../bin/DataQualityCheck

.PHONY : examples/CMakeFiles/DataQualityCheck.dir/build

examples/CMakeFiles/DataQualityCheck.dir/requires: examples/CMakeFiles/DataQualityCheck.dir/babyMindDataQualityCheck.cpp.o.requires

.PHONY : examples/CMakeFiles/DataQualityCheck.dir/requires

examples/CMakeFiles/DataQualityCheck.dir/clean:
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/DataQualityCheck.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/DataQualityCheck.dir/clean

examples/CMakeFiles/DataQualityCheck.dir/depend:
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22 /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/examples /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples/CMakeFiles/DataQualityCheck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/DataQualityCheck.dir/depend

