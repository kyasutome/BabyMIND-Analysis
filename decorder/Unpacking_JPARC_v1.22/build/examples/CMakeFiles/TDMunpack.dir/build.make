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
include examples/CMakeFiles/TDMunpack.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/TDMunpack.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/TDMunpack.dir/flags.make

examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o: examples/CMakeFiles/TDMunpack.dir/flags.make
examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o: ../examples/babyMINDTDMUnpack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o"
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples && /Applications/Xcode9.1.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o -c /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/examples/babyMINDTDMUnpack.cpp

examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.i"
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples && /Applications/Xcode9.1.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/examples/babyMINDTDMUnpack.cpp > CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.i

examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.s"
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples && /Applications/Xcode9.1.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/examples/babyMINDTDMUnpack.cpp -o CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.s

examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o.requires:

.PHONY : examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o.requires

examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o.provides: examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/TDMunpack.dir/build.make examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o.provides.build
.PHONY : examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o.provides

examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o.provides.build: examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o


# Object files for target TDMunpack
TDMunpack_OBJECTS = \
"CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o"

# External object files for target TDMunpack
TDMunpack_EXTERNAL_OBJECTS =

../bin/TDMunpack: examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o
../bin/TDMunpack: examples/CMakeFiles/TDMunpack.dir/build.make
../bin/TDMunpack: ../lib/libBabyMINDUnpack.dylib
../bin/TDMunpack: examples/CMakeFiles/TDMunpack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/TDMunpack"
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TDMunpack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/TDMunpack.dir/build: ../bin/TDMunpack

.PHONY : examples/CMakeFiles/TDMunpack.dir/build

examples/CMakeFiles/TDMunpack.dir/requires: examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o.requires

.PHONY : examples/CMakeFiles/TDMunpack.dir/requires

examples/CMakeFiles/TDMunpack.dir/clean:
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/TDMunpack.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/TDMunpack.dir/clean

examples/CMakeFiles/TDMunpack.dir/depend:
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22 /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/examples /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.22/build/examples/CMakeFiles/TDMunpack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/TDMunpack.dir/depend

