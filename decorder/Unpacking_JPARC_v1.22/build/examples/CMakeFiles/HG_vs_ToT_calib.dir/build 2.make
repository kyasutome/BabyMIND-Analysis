# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.9.3_1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.9.3_1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/HG_vs_ToT_calib.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/HG_vs_ToT_calib.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/HG_vs_ToT_calib.dir/flags.make

examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o: examples/CMakeFiles/HG_vs_ToT_calib.dir/flags.make
examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o: ../examples/HG_vs_ToT_calib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o"
	cd /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/build/examples && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o -c /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/examples/HG_vs_ToT_calib.cpp

examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.i"
	cd /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/build/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/examples/HG_vs_ToT_calib.cpp > CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.i

examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.s"
	cd /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/build/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/examples/HG_vs_ToT_calib.cpp -o CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.s

examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o.requires:

.PHONY : examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o.requires

examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o.provides: examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/HG_vs_ToT_calib.dir/build.make examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o.provides.build
.PHONY : examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o.provides

examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o.provides.build: examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o


# Object files for target HG_vs_ToT_calib
HG_vs_ToT_calib_OBJECTS = \
"CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o"

# External object files for target HG_vs_ToT_calib
HG_vs_ToT_calib_EXTERNAL_OBJECTS =

../bin/HG_vs_ToT_calib: examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o
../bin/HG_vs_ToT_calib: examples/CMakeFiles/HG_vs_ToT_calib.dir/build.make
../bin/HG_vs_ToT_calib: ../lib/libBabyMINDUnpack.dylib
../bin/HG_vs_ToT_calib: examples/CMakeFiles/HG_vs_ToT_calib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/HG_vs_ToT_calib"
	cd /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HG_vs_ToT_calib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/HG_vs_ToT_calib.dir/build: ../bin/HG_vs_ToT_calib

.PHONY : examples/CMakeFiles/HG_vs_ToT_calib.dir/build

examples/CMakeFiles/HG_vs_ToT_calib.dir/requires: examples/CMakeFiles/HG_vs_ToT_calib.dir/HG_vs_ToT_calib.cpp.o.requires

.PHONY : examples/CMakeFiles/HG_vs_ToT_calib.dir/requires

examples/CMakeFiles/HG_vs_ToT_calib.dir/clean:
	cd /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/HG_vs_ToT_calib.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/HG_vs_ToT_calib.dir/clean

examples/CMakeFiles/HG_vs_ToT_calib.dir/depend:
	cd /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2 /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/examples /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/build /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/build/examples /Volumes/DriveGenius/JPARC/Unpacking_JPARC_v1.2/build/examples/CMakeFiles/HG_vs_ToT_calib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/HG_vs_ToT_calib.dir/depend

