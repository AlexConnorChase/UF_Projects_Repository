# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/funandgames/Desktop/CLionProjects/CacheProjectAC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/funandgames/Desktop/CLionProjects/CacheProjectAC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CacheProjectAC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CacheProjectAC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CacheProjectAC.dir/flags.make

CMakeFiles/CacheProjectAC.dir/main.cpp.o: CMakeFiles/CacheProjectAC.dir/flags.make
CMakeFiles/CacheProjectAC.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/funandgames/Desktop/CLionProjects/CacheProjectAC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CacheProjectAC.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CacheProjectAC.dir/main.cpp.o -c /Users/funandgames/Desktop/CLionProjects/CacheProjectAC/main.cpp

CMakeFiles/CacheProjectAC.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CacheProjectAC.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/funandgames/Desktop/CLionProjects/CacheProjectAC/main.cpp > CMakeFiles/CacheProjectAC.dir/main.cpp.i

CMakeFiles/CacheProjectAC.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CacheProjectAC.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/funandgames/Desktop/CLionProjects/CacheProjectAC/main.cpp -o CMakeFiles/CacheProjectAC.dir/main.cpp.s

# Object files for target CacheProjectAC
CacheProjectAC_OBJECTS = \
"CMakeFiles/CacheProjectAC.dir/main.cpp.o"

# External object files for target CacheProjectAC
CacheProjectAC_EXTERNAL_OBJECTS =

CacheProjectAC: CMakeFiles/CacheProjectAC.dir/main.cpp.o
CacheProjectAC: CMakeFiles/CacheProjectAC.dir/build.make
CacheProjectAC: CMakeFiles/CacheProjectAC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/funandgames/Desktop/CLionProjects/CacheProjectAC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CacheProjectAC"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CacheProjectAC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CacheProjectAC.dir/build: CacheProjectAC

.PHONY : CMakeFiles/CacheProjectAC.dir/build

CMakeFiles/CacheProjectAC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CacheProjectAC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CacheProjectAC.dir/clean

CMakeFiles/CacheProjectAC.dir/depend:
	cd /Users/funandgames/Desktop/CLionProjects/CacheProjectAC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/funandgames/Desktop/CLionProjects/CacheProjectAC /Users/funandgames/Desktop/CLionProjects/CacheProjectAC /Users/funandgames/Desktop/CLionProjects/CacheProjectAC/cmake-build-debug /Users/funandgames/Desktop/CLionProjects/CacheProjectAC/cmake-build-debug /Users/funandgames/Desktop/CLionProjects/CacheProjectAC/cmake-build-debug/CMakeFiles/CacheProjectAC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CacheProjectAC.dir/depend

