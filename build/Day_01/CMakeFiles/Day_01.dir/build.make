# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake/bin/cmake

# The command to remove a file.
RM = /opt/cmake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/advent-of-code/amir

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/advent-of-code/amir/build

# Include any dependencies generated for this target.
include Day_01/CMakeFiles/Day_01.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Day_01/CMakeFiles/Day_01.dir/compiler_depend.make

# Include the progress variables for this target.
include Day_01/CMakeFiles/Day_01.dir/progress.make

# Include the compile flags for this target's objects.
include Day_01/CMakeFiles/Day_01.dir/flags.make

Day_01/CMakeFiles/Day_01.dir/Day_01.c.o: Day_01/CMakeFiles/Day_01.dir/flags.make
Day_01/CMakeFiles/Day_01.dir/Day_01.c.o: ../Day_01/Day_01.c
Day_01/CMakeFiles/Day_01.dir/Day_01.c.o: Day_01/CMakeFiles/Day_01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/advent-of-code/amir/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Day_01/CMakeFiles/Day_01.dir/Day_01.c.o"
	cd /workspaces/advent-of-code/amir/build/Day_01 && /usr/bin/aarch64-linux-gnu-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Day_01/CMakeFiles/Day_01.dir/Day_01.c.o -MF CMakeFiles/Day_01.dir/Day_01.c.o.d -o CMakeFiles/Day_01.dir/Day_01.c.o -c /workspaces/advent-of-code/amir/Day_01/Day_01.c

Day_01/CMakeFiles/Day_01.dir/Day_01.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Day_01.dir/Day_01.c.i"
	cd /workspaces/advent-of-code/amir/build/Day_01 && /usr/bin/aarch64-linux-gnu-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/advent-of-code/amir/Day_01/Day_01.c > CMakeFiles/Day_01.dir/Day_01.c.i

Day_01/CMakeFiles/Day_01.dir/Day_01.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Day_01.dir/Day_01.c.s"
	cd /workspaces/advent-of-code/amir/build/Day_01 && /usr/bin/aarch64-linux-gnu-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/advent-of-code/amir/Day_01/Day_01.c -o CMakeFiles/Day_01.dir/Day_01.c.s

# Object files for target Day_01
Day_01_OBJECTS = \
"CMakeFiles/Day_01.dir/Day_01.c.o"

# External object files for target Day_01
Day_01_EXTERNAL_OBJECTS =

Day_01/Day_01: Day_01/CMakeFiles/Day_01.dir/Day_01.c.o
Day_01/Day_01: Day_01/CMakeFiles/Day_01.dir/build.make
Day_01/Day_01: Day_01/CMakeFiles/Day_01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/advent-of-code/amir/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Day_01"
	cd /workspaces/advent-of-code/amir/build/Day_01 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Day_01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Day_01/CMakeFiles/Day_01.dir/build: Day_01/Day_01
.PHONY : Day_01/CMakeFiles/Day_01.dir/build

Day_01/CMakeFiles/Day_01.dir/clean:
	cd /workspaces/advent-of-code/amir/build/Day_01 && $(CMAKE_COMMAND) -P CMakeFiles/Day_01.dir/cmake_clean.cmake
.PHONY : Day_01/CMakeFiles/Day_01.dir/clean

Day_01/CMakeFiles/Day_01.dir/depend:
	cd /workspaces/advent-of-code/amir/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/advent-of-code/amir /workspaces/advent-of-code/amir/Day_01 /workspaces/advent-of-code/amir/build /workspaces/advent-of-code/amir/build/Day_01 /workspaces/advent-of-code/amir/build/Day_01/CMakeFiles/Day_01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Day_01/CMakeFiles/Day_01.dir/depend

