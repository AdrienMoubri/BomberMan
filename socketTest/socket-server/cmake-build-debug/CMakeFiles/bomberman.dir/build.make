# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.1.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.1.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\AMO\Documents\ecole\BomberMan\BomberMan\socketTest\socket-server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\AMO\Documents\ecole\BomberMan\BomberMan\socketTest\socket-server\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bomberman.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bomberman.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bomberman.dir/flags.make

CMakeFiles/bomberman.dir/main.c.obj: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\AMO\Documents\ecole\BomberMan\BomberMan\socketTest\socket-server\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/bomberman.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\bomberman.dir\main.c.obj   -c C:\Users\AMO\Documents\ecole\BomberMan\BomberMan\socketTest\socket-server\main.c

CMakeFiles/bomberman.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bomberman.dir/main.c.i"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\AMO\Documents\ecole\BomberMan\BomberMan\socketTest\socket-server\main.c > CMakeFiles\bomberman.dir\main.c.i

CMakeFiles/bomberman.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bomberman.dir/main.c.s"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\AMO\Documents\ecole\BomberMan\BomberMan\socketTest\socket-server\main.c -o CMakeFiles\bomberman.dir\main.c.s

CMakeFiles/bomberman.dir/main.c.obj.requires:

.PHONY : CMakeFiles/bomberman.dir/main.c.obj.requires

CMakeFiles/bomberman.dir/main.c.obj.provides: CMakeFiles/bomberman.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles\bomberman.dir\build.make CMakeFiles/bomberman.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/bomberman.dir/main.c.obj.provides

CMakeFiles/bomberman.dir/main.c.obj.provides.build: CMakeFiles/bomberman.dir/main.c.obj


# Object files for target bomberman
bomberman_OBJECTS = \
"CMakeFiles/bomberman.dir/main.c.obj"

# External object files for target bomberman
bomberman_EXTERNAL_OBJECTS =

bomberman.exe: CMakeFiles/bomberman.dir/main.c.obj
bomberman.exe: CMakeFiles/bomberman.dir/build.make
bomberman.exe: CMakeFiles/bomberman.dir/linklibs.rsp
bomberman.exe: CMakeFiles/bomberman.dir/objects1.rsp
bomberman.exe: CMakeFiles/bomberman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\AMO\Documents\ecole\BomberMan\BomberMan\socketTest\socket-server\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bomberman.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bomberman.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bomberman.dir/build: bomberman.exe

.PHONY : CMakeFiles/bomberman.dir/build

CMakeFiles/bomberman.dir/requires: CMakeFiles/bomberman.dir/main.c.obj.requires

.PHONY : CMakeFiles/bomberman.dir/requires

CMakeFiles/bomberman.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\bomberman.dir\cmake_clean.cmake
.PHONY : CMakeFiles/bomberman.dir/clean

CMakeFiles/bomberman.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\AMO\Documents\ecole\BomberMan\BomberMan\socketTest\socket-server C:\Users\AMO\Documents\ecole\BomberMan\BomberMan\socketTest\socket-server C:\Users\AMO\Documents\ecole\BomberMan\BomberMan\socketTest\socket-server\cmake-build-debug C:\Users\AMO\Documents\ecole\BomberMan\BomberMan\socketTest\socket-server\cmake-build-debug C:\Users\AMO\Documents\ecole\BomberMan\BomberMan\socketTest\socket-server\cmake-build-debug\CMakeFiles\bomberman.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bomberman.dir/depend

