# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.24.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.24.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/yeonseong/openGL/t/03_triangle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/yeonseong/openGL/t/03_triangle

# Include any dependencies generated for this target.
include CMakeFiles/HelloTriangle.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HelloTriangle.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HelloTriangle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HelloTriangle.dir/flags.make

CMakeFiles/HelloTriangle.dir/source/glad.c.o: CMakeFiles/HelloTriangle.dir/flags.make
CMakeFiles/HelloTriangle.dir/source/glad.c.o: source/glad.c
CMakeFiles/HelloTriangle.dir/source/glad.c.o: CMakeFiles/HelloTriangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yeonseong/openGL/t/03_triangle/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/HelloTriangle.dir/source/glad.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/HelloTriangle.dir/source/glad.c.o -MF CMakeFiles/HelloTriangle.dir/source/glad.c.o.d -o CMakeFiles/HelloTriangle.dir/source/glad.c.o -c /Users/yeonseong/openGL/t/03_triangle/source/glad.c

CMakeFiles/HelloTriangle.dir/source/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HelloTriangle.dir/source/glad.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yeonseong/openGL/t/03_triangle/source/glad.c > CMakeFiles/HelloTriangle.dir/source/glad.c.i

CMakeFiles/HelloTriangle.dir/source/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HelloTriangle.dir/source/glad.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yeonseong/openGL/t/03_triangle/source/glad.c -o CMakeFiles/HelloTriangle.dir/source/glad.c.s

CMakeFiles/HelloTriangle.dir/source/main.cpp.o: CMakeFiles/HelloTriangle.dir/flags.make
CMakeFiles/HelloTriangle.dir/source/main.cpp.o: source/main.cpp
CMakeFiles/HelloTriangle.dir/source/main.cpp.o: CMakeFiles/HelloTriangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yeonseong/openGL/t/03_triangle/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HelloTriangle.dir/source/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HelloTriangle.dir/source/main.cpp.o -MF CMakeFiles/HelloTriangle.dir/source/main.cpp.o.d -o CMakeFiles/HelloTriangle.dir/source/main.cpp.o -c /Users/yeonseong/openGL/t/03_triangle/source/main.cpp

CMakeFiles/HelloTriangle.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloTriangle.dir/source/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yeonseong/openGL/t/03_triangle/source/main.cpp > CMakeFiles/HelloTriangle.dir/source/main.cpp.i

CMakeFiles/HelloTriangle.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloTriangle.dir/source/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yeonseong/openGL/t/03_triangle/source/main.cpp -o CMakeFiles/HelloTriangle.dir/source/main.cpp.s

# Object files for target HelloTriangle
HelloTriangle_OBJECTS = \
"CMakeFiles/HelloTriangle.dir/source/glad.c.o" \
"CMakeFiles/HelloTriangle.dir/source/main.cpp.o"

# External object files for target HelloTriangle
HelloTriangle_EXTERNAL_OBJECTS =

HelloTriangle: CMakeFiles/HelloTriangle.dir/source/glad.c.o
HelloTriangle: CMakeFiles/HelloTriangle.dir/source/main.cpp.o
HelloTriangle: CMakeFiles/HelloTriangle.dir/build.make
HelloTriangle: glfw-3.3.8/src/libglfw3.a
HelloTriangle: CMakeFiles/HelloTriangle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/yeonseong/openGL/t/03_triangle/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable HelloTriangle"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HelloTriangle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HelloTriangle.dir/build: HelloTriangle
.PHONY : CMakeFiles/HelloTriangle.dir/build

CMakeFiles/HelloTriangle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HelloTriangle.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HelloTriangle.dir/clean

CMakeFiles/HelloTriangle.dir/depend:
	cd /Users/yeonseong/openGL/t/03_triangle && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/yeonseong/openGL/t/03_triangle /Users/yeonseong/openGL/t/03_triangle /Users/yeonseong/openGL/t/03_triangle /Users/yeonseong/openGL/t/03_triangle /Users/yeonseong/openGL/t/03_triangle/CMakeFiles/HelloTriangle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HelloTriangle.dir/depend

