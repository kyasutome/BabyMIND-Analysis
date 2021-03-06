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
CMAKE_SOURCE_DIR = /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build

# Include any dependencies generated for this target.
include src/DetPerform/CMakeFiles/pedist.dir/depend.make

# Include the progress variables for this target.
include src/DetPerform/CMakeFiles/pedist.dir/progress.make

# Include the compile flags for this target's objects.
include src/DetPerform/CMakeFiles/pedist.dir/flags.make

src/DetPerform/CMakeFiles/pedist.dir/pedist.cpp.o: src/DetPerform/CMakeFiles/pedist.dir/flags.make
src/DetPerform/CMakeFiles/pedist.dir/pedist.cpp.o: ../src/DetPerform/pedist.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/DetPerform/CMakeFiles/pedist.dir/pedist.cpp.o"
	cd /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/DetPerform && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pedist.dir/pedist.cpp.o -c /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/src/DetPerform/pedist.cpp

src/DetPerform/CMakeFiles/pedist.dir/pedist.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pedist.dir/pedist.cpp.i"
	cd /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/DetPerform && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/src/DetPerform/pedist.cpp > CMakeFiles/pedist.dir/pedist.cpp.i

src/DetPerform/CMakeFiles/pedist.dir/pedist.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pedist.dir/pedist.cpp.s"
	cd /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/DetPerform && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/src/DetPerform/pedist.cpp -o CMakeFiles/pedist.dir/pedist.cpp.s

# Object files for target pedist
pedist_OBJECTS = \
"CMakeFiles/pedist.dir/pedist.cpp.o"

# External object files for target pedist
pedist_EXTERNAL_OBJECTS =

../bin/pedist: src/DetPerform/CMakeFiles/pedist.dir/pedist.cpp.o
../bin/pedist: src/DetPerform/CMakeFiles/pedist.dir/build.make
../bin/pedist: ../lib/library/BMBasicRecon.so
../bin/pedist: ../lib/library/BMBeaminfo.so
../bin/pedist: ../lib/library/BMBSD.so
../bin/pedist: ../lib/library/BasicRecon.so
../bin/pedist: src/DetPerform/CMakeFiles/pedist.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/pedist"
	cd /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/DetPerform && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pedist.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/DetPerform/CMakeFiles/pedist.dir/build: ../bin/pedist

.PHONY : src/DetPerform/CMakeFiles/pedist.dir/build

src/DetPerform/CMakeFiles/pedist.dir/clean:
	cd /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/DetPerform && $(CMAKE_COMMAND) -P CMakeFiles/pedist.dir/cmake_clean.cmake
.PHONY : src/DetPerform/CMakeFiles/pedist.dir/clean

src/DetPerform/CMakeFiles/pedist.dir/depend:
	cd /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/src/DetPerform /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/DetPerform /Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/build/src/DetPerform/CMakeFiles/pedist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/DetPerform/CMakeFiles/pedist.dir/depend

