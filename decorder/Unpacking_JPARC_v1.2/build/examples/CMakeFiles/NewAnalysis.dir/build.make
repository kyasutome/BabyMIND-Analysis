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
CMAKE_SOURCE_DIR = /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/NewAnalysis.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/NewAnalysis.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/NewAnalysis.dir/flags.make

examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o: examples/CMakeFiles/NewAnalysis.dir/flags.make
examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o: ../examples/new_analysis.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o"
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/build/examples && /Applications/Xcode9.1.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o -c /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/examples/new_analysis.cpp

examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NewAnalysis.dir/new_analysis.cpp.i"
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/build/examples && /Applications/Xcode9.1.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/examples/new_analysis.cpp > CMakeFiles/NewAnalysis.dir/new_analysis.cpp.i

examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NewAnalysis.dir/new_analysis.cpp.s"
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/build/examples && /Applications/Xcode9.1.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/examples/new_analysis.cpp -o CMakeFiles/NewAnalysis.dir/new_analysis.cpp.s

examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o.requires:

.PHONY : examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o.requires

examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o.provides: examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/NewAnalysis.dir/build.make examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o.provides.build
.PHONY : examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o.provides

examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o.provides.build: examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o


# Object files for target NewAnalysis
NewAnalysis_OBJECTS = \
"CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o"

# External object files for target NewAnalysis
NewAnalysis_EXTERNAL_OBJECTS =

../bin/NewAnalysis: examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o
../bin/NewAnalysis: examples/CMakeFiles/NewAnalysis.dir/build.make
../bin/NewAnalysis: ../lib/libBabyMINDUnpack.dylib
../bin/NewAnalysis: examples/CMakeFiles/NewAnalysis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/NewAnalysis"
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NewAnalysis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/NewAnalysis.dir/build: ../bin/NewAnalysis

.PHONY : examples/CMakeFiles/NewAnalysis.dir/build

examples/CMakeFiles/NewAnalysis.dir/requires: examples/CMakeFiles/NewAnalysis.dir/new_analysis.cpp.o.requires

.PHONY : examples/CMakeFiles/NewAnalysis.dir/requires

examples/CMakeFiles/NewAnalysis.dir/clean:
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/NewAnalysis.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/NewAnalysis.dir/clean

examples/CMakeFiles/NewAnalysis.dir/depend:
	cd /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2 /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/examples /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/build /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/build/examples /Users/jinaren/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.2/build/examples/CMakeFiles/NewAnalysis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/NewAnalysis.dir/depend

