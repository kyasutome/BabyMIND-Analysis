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
CMAKE_SOURCE_DIR = /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/TDMunpack.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/TDMunpack.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/TDMunpack.dir/flags.make

examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o: examples/CMakeFiles/TDMunpack.dir/flags.make
examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o: ../examples/babyMINDTDMUnpack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o"
	cd /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/build/examples && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o -c /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/examples/babyMINDTDMUnpack.cpp

examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.i"
	cd /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/build/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/examples/babyMINDTDMUnpack.cpp > CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.i

examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.s"
	cd /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/build/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/examples/babyMINDTDMUnpack.cpp -o CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.s

# Object files for target TDMunpack
TDMunpack_OBJECTS = \
"CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o"

# External object files for target TDMunpack
TDMunpack_EXTERNAL_OBJECTS =

../bin/TDMunpack: examples/CMakeFiles/TDMunpack.dir/babyMINDTDMUnpack.cpp.o
../bin/TDMunpack: examples/CMakeFiles/TDMunpack.dir/build.make
../bin/TDMunpack: ../lib/libBabyMINDUnpack.dylib
../bin/TDMunpack: examples/CMakeFiles/TDMunpack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/TDMunpack"
	cd /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TDMunpack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/TDMunpack.dir/build: ../bin/TDMunpack

.PHONY : examples/CMakeFiles/TDMunpack.dir/build

examples/CMakeFiles/TDMunpack.dir/clean:
	cd /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/TDMunpack.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/TDMunpack.dir/clean

examples/CMakeFiles/TDMunpack.dir/depend:
	cd /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35 /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/examples /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/build /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/build/examples /Users/kenji/Dropbox/wagasci/babymind/software/analysis/decorder/Unpacking_JPARC_v1.35/build/examples/CMakeFiles/TDMunpack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/TDMunpack.dir/depend

