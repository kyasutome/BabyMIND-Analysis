# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/Calibration_txt.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/Calibration_txt.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/Calibration_txt.dir/flags.make

examples/CMakeFiles/Calibration_txt.dir/Calibration_txt.cpp.o: examples/CMakeFiles/Calibration_txt.dir/flags.make
examples/CMakeFiles/Calibration_txt.dir/Calibration_txt.cpp.o: ../examples/Calibration_txt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/Calibration_txt.dir/Calibration_txt.cpp.o"
	cd /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/build/examples && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Calibration_txt.dir/Calibration_txt.cpp.o -c /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/examples/Calibration_txt.cpp

examples/CMakeFiles/Calibration_txt.dir/Calibration_txt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Calibration_txt.dir/Calibration_txt.cpp.i"
	cd /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/build/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/examples/Calibration_txt.cpp > CMakeFiles/Calibration_txt.dir/Calibration_txt.cpp.i

examples/CMakeFiles/Calibration_txt.dir/Calibration_txt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Calibration_txt.dir/Calibration_txt.cpp.s"
	cd /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/build/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/examples/Calibration_txt.cpp -o CMakeFiles/Calibration_txt.dir/Calibration_txt.cpp.s

# Object files for target Calibration_txt
Calibration_txt_OBJECTS = \
"CMakeFiles/Calibration_txt.dir/Calibration_txt.cpp.o"

# External object files for target Calibration_txt
Calibration_txt_EXTERNAL_OBJECTS =

../bin/Calibration_txt: examples/CMakeFiles/Calibration_txt.dir/Calibration_txt.cpp.o
../bin/Calibration_txt: examples/CMakeFiles/Calibration_txt.dir/build.make
../bin/Calibration_txt: ../lib/libBabyMINDUnpack.dylib
../bin/Calibration_txt: examples/CMakeFiles/Calibration_txt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/Calibration_txt"
	cd /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Calibration_txt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/Calibration_txt.dir/build: ../bin/Calibration_txt

.PHONY : examples/CMakeFiles/Calibration_txt.dir/build

examples/CMakeFiles/Calibration_txt.dir/clean:
	cd /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/Calibration_txt.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/Calibration_txt.dir/clean

examples/CMakeFiles/Calibration_txt.dir/depend:
	cd /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31 /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/examples /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/build /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/build/examples /Users/kenji/Documents/document_jinaren/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Decorder/Unpacking_JPARC_v1.31/build/examples/CMakeFiles/Calibration_txt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/Calibration_txt.dir/depend

