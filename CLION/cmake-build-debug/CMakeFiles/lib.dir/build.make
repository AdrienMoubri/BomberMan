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
CMAKE_SOURCE_DIR = C:\Users\AMO\Desktop\BomberMan\bfm\CLION

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\AMO\Desktop\BomberMan\bfm\CLION\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lib.dir/flags.make

CMakeFiles/lib.dir/src/lib/readline.c.obj: CMakeFiles/lib.dir/flags.make
CMakeFiles/lib.dir/src/lib/readline.c.obj: CMakeFiles/lib.dir/includes_C.rsp
CMakeFiles/lib.dir/src/lib/readline.c.obj: ../src/lib/readline.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\AMO\Desktop\BomberMan\bfm\CLION\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lib.dir/src/lib/readline.c.obj"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\lib.dir\src\lib\readline.c.obj   -c C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\readline.c

CMakeFiles/lib.dir/src/lib/readline.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib.dir/src/lib/readline.c.i"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\readline.c > CMakeFiles\lib.dir\src\lib\readline.c.i

CMakeFiles/lib.dir/src/lib/readline.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib.dir/src/lib/readline.c.s"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\readline.c -o CMakeFiles\lib.dir\src\lib\readline.c.s

CMakeFiles/lib.dir/src/lib/readline.c.obj.requires:

.PHONY : CMakeFiles/lib.dir/src/lib/readline.c.obj.requires

CMakeFiles/lib.dir/src/lib/readline.c.obj.provides: CMakeFiles/lib.dir/src/lib/readline.c.obj.requires
	$(MAKE) -f CMakeFiles\lib.dir\build.make CMakeFiles/lib.dir/src/lib/readline.c.obj.provides.build
.PHONY : CMakeFiles/lib.dir/src/lib/readline.c.obj.provides

CMakeFiles/lib.dir/src/lib/readline.c.obj.provides.build: CMakeFiles/lib.dir/src/lib/readline.c.obj


CMakeFiles/lib.dir/src/lib/my_string.c.obj: CMakeFiles/lib.dir/flags.make
CMakeFiles/lib.dir/src/lib/my_string.c.obj: CMakeFiles/lib.dir/includes_C.rsp
CMakeFiles/lib.dir/src/lib/my_string.c.obj: ../src/lib/my_string.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\AMO\Desktop\BomberMan\bfm\CLION\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/lib.dir/src/lib/my_string.c.obj"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\lib.dir\src\lib\my_string.c.obj   -c C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_string.c

CMakeFiles/lib.dir/src/lib/my_string.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib.dir/src/lib/my_string.c.i"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_string.c > CMakeFiles\lib.dir\src\lib\my_string.c.i

CMakeFiles/lib.dir/src/lib/my_string.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib.dir/src/lib/my_string.c.s"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_string.c -o CMakeFiles\lib.dir\src\lib\my_string.c.s

CMakeFiles/lib.dir/src/lib/my_string.c.obj.requires:

.PHONY : CMakeFiles/lib.dir/src/lib/my_string.c.obj.requires

CMakeFiles/lib.dir/src/lib/my_string.c.obj.provides: CMakeFiles/lib.dir/src/lib/my_string.c.obj.requires
	$(MAKE) -f CMakeFiles\lib.dir\build.make CMakeFiles/lib.dir/src/lib/my_string.c.obj.provides.build
.PHONY : CMakeFiles/lib.dir/src/lib/my_string.c.obj.provides

CMakeFiles/lib.dir/src/lib/my_string.c.obj.provides.build: CMakeFiles/lib.dir/src/lib/my_string.c.obj


CMakeFiles/lib.dir/src/lib/my_strcat.c.obj: CMakeFiles/lib.dir/flags.make
CMakeFiles/lib.dir/src/lib/my_strcat.c.obj: CMakeFiles/lib.dir/includes_C.rsp
CMakeFiles/lib.dir/src/lib/my_strcat.c.obj: ../src/lib/my_strcat.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\AMO\Desktop\BomberMan\bfm\CLION\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/lib.dir/src/lib/my_strcat.c.obj"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\lib.dir\src\lib\my_strcat.c.obj   -c C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_strcat.c

CMakeFiles/lib.dir/src/lib/my_strcat.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib.dir/src/lib/my_strcat.c.i"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_strcat.c > CMakeFiles\lib.dir\src\lib\my_strcat.c.i

CMakeFiles/lib.dir/src/lib/my_strcat.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib.dir/src/lib/my_strcat.c.s"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_strcat.c -o CMakeFiles\lib.dir\src\lib\my_strcat.c.s

CMakeFiles/lib.dir/src/lib/my_strcat.c.obj.requires:

.PHONY : CMakeFiles/lib.dir/src/lib/my_strcat.c.obj.requires

CMakeFiles/lib.dir/src/lib/my_strcat.c.obj.provides: CMakeFiles/lib.dir/src/lib/my_strcat.c.obj.requires
	$(MAKE) -f CMakeFiles\lib.dir\build.make CMakeFiles/lib.dir/src/lib/my_strcat.c.obj.provides.build
.PHONY : CMakeFiles/lib.dir/src/lib/my_strcat.c.obj.provides

CMakeFiles/lib.dir/src/lib/my_strcat.c.obj.provides.build: CMakeFiles/lib.dir/src/lib/my_strcat.c.obj


CMakeFiles/lib.dir/src/lib/my_rand.c.obj: CMakeFiles/lib.dir/flags.make
CMakeFiles/lib.dir/src/lib/my_rand.c.obj: CMakeFiles/lib.dir/includes_C.rsp
CMakeFiles/lib.dir/src/lib/my_rand.c.obj: ../src/lib/my_rand.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\AMO\Desktop\BomberMan\bfm\CLION\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/lib.dir/src/lib/my_rand.c.obj"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\lib.dir\src\lib\my_rand.c.obj   -c C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_rand.c

CMakeFiles/lib.dir/src/lib/my_rand.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib.dir/src/lib/my_rand.c.i"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_rand.c > CMakeFiles\lib.dir\src\lib\my_rand.c.i

CMakeFiles/lib.dir/src/lib/my_rand.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib.dir/src/lib/my_rand.c.s"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_rand.c -o CMakeFiles\lib.dir\src\lib\my_rand.c.s

CMakeFiles/lib.dir/src/lib/my_rand.c.obj.requires:

.PHONY : CMakeFiles/lib.dir/src/lib/my_rand.c.obj.requires

CMakeFiles/lib.dir/src/lib/my_rand.c.obj.provides: CMakeFiles/lib.dir/src/lib/my_rand.c.obj.requires
	$(MAKE) -f CMakeFiles\lib.dir\build.make CMakeFiles/lib.dir/src/lib/my_rand.c.obj.provides.build
.PHONY : CMakeFiles/lib.dir/src/lib/my_rand.c.obj.provides

CMakeFiles/lib.dir/src/lib/my_rand.c.obj.provides.build: CMakeFiles/lib.dir/src/lib/my_rand.c.obj


CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj: CMakeFiles/lib.dir/flags.make
CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj: CMakeFiles/lib.dir/includes_C.rsp
CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj: ../src/lib/my_getnbr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\AMO\Desktop\BomberMan\bfm\CLION\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\lib.dir\src\lib\my_getnbr.c.obj   -c C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_getnbr.c

CMakeFiles/lib.dir/src/lib/my_getnbr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib.dir/src/lib/my_getnbr.c.i"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_getnbr.c > CMakeFiles\lib.dir\src\lib\my_getnbr.c.i

CMakeFiles/lib.dir/src/lib/my_getnbr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib.dir/src/lib/my_getnbr.c.s"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_getnbr.c -o CMakeFiles\lib.dir\src\lib\my_getnbr.c.s

CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj.requires:

.PHONY : CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj.requires

CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj.provides: CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj.requires
	$(MAKE) -f CMakeFiles\lib.dir\build.make CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj.provides.build
.PHONY : CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj.provides

CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj.provides.build: CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj


CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj: CMakeFiles/lib.dir/flags.make
CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj: CMakeFiles/lib.dir/includes_C.rsp
CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj: ../src/lib/my_put_nbr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\AMO\Desktop\BomberMan\bfm\CLION\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\lib.dir\src\lib\my_put_nbr.c.obj   -c C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_put_nbr.c

CMakeFiles/lib.dir/src/lib/my_put_nbr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib.dir/src/lib/my_put_nbr.c.i"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_put_nbr.c > CMakeFiles\lib.dir\src\lib\my_put_nbr.c.i

CMakeFiles/lib.dir/src/lib/my_put_nbr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib.dir/src/lib/my_put_nbr.c.s"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_put_nbr.c -o CMakeFiles\lib.dir\src\lib\my_put_nbr.c.s

CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj.requires:

.PHONY : CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj.requires

CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj.provides: CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj.requires
	$(MAKE) -f CMakeFiles\lib.dir\build.make CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj.provides.build
.PHONY : CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj.provides

CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj.provides.build: CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj


CMakeFiles/lib.dir/src/lib/my_putchar.c.obj: CMakeFiles/lib.dir/flags.make
CMakeFiles/lib.dir/src/lib/my_putchar.c.obj: CMakeFiles/lib.dir/includes_C.rsp
CMakeFiles/lib.dir/src/lib/my_putchar.c.obj: ../src/lib/my_putchar.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\AMO\Desktop\BomberMan\bfm\CLION\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/lib.dir/src/lib/my_putchar.c.obj"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\lib.dir\src\lib\my_putchar.c.obj   -c C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_putchar.c

CMakeFiles/lib.dir/src/lib/my_putchar.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib.dir/src/lib/my_putchar.c.i"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_putchar.c > CMakeFiles\lib.dir\src\lib\my_putchar.c.i

CMakeFiles/lib.dir/src/lib/my_putchar.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib.dir/src/lib/my_putchar.c.s"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\AMO\Desktop\BomberMan\bfm\CLION\src\lib\my_putchar.c -o CMakeFiles\lib.dir\src\lib\my_putchar.c.s

CMakeFiles/lib.dir/src/lib/my_putchar.c.obj.requires:

.PHONY : CMakeFiles/lib.dir/src/lib/my_putchar.c.obj.requires

CMakeFiles/lib.dir/src/lib/my_putchar.c.obj.provides: CMakeFiles/lib.dir/src/lib/my_putchar.c.obj.requires
	$(MAKE) -f CMakeFiles\lib.dir\build.make CMakeFiles/lib.dir/src/lib/my_putchar.c.obj.provides.build
.PHONY : CMakeFiles/lib.dir/src/lib/my_putchar.c.obj.provides

CMakeFiles/lib.dir/src/lib/my_putchar.c.obj.provides.build: CMakeFiles/lib.dir/src/lib/my_putchar.c.obj


# Object files for target lib
lib_OBJECTS = \
"CMakeFiles/lib.dir/src/lib/readline.c.obj" \
"CMakeFiles/lib.dir/src/lib/my_string.c.obj" \
"CMakeFiles/lib.dir/src/lib/my_strcat.c.obj" \
"CMakeFiles/lib.dir/src/lib/my_rand.c.obj" \
"CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj" \
"CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj" \
"CMakeFiles/lib.dir/src/lib/my_putchar.c.obj"

# External object files for target lib
lib_EXTERNAL_OBJECTS =

liblib.a: CMakeFiles/lib.dir/src/lib/readline.c.obj
liblib.a: CMakeFiles/lib.dir/src/lib/my_string.c.obj
liblib.a: CMakeFiles/lib.dir/src/lib/my_strcat.c.obj
liblib.a: CMakeFiles/lib.dir/src/lib/my_rand.c.obj
liblib.a: CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj
liblib.a: CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj
liblib.a: CMakeFiles/lib.dir/src/lib/my_putchar.c.obj
liblib.a: CMakeFiles/lib.dir/build.make
liblib.a: CMakeFiles/lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\AMO\Desktop\BomberMan\bfm\CLION\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C static library liblib.a"
	$(CMAKE_COMMAND) -P CMakeFiles\lib.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lib.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lib.dir/build: liblib.a

.PHONY : CMakeFiles/lib.dir/build

CMakeFiles/lib.dir/requires: CMakeFiles/lib.dir/src/lib/readline.c.obj.requires
CMakeFiles/lib.dir/requires: CMakeFiles/lib.dir/src/lib/my_string.c.obj.requires
CMakeFiles/lib.dir/requires: CMakeFiles/lib.dir/src/lib/my_strcat.c.obj.requires
CMakeFiles/lib.dir/requires: CMakeFiles/lib.dir/src/lib/my_rand.c.obj.requires
CMakeFiles/lib.dir/requires: CMakeFiles/lib.dir/src/lib/my_getnbr.c.obj.requires
CMakeFiles/lib.dir/requires: CMakeFiles/lib.dir/src/lib/my_put_nbr.c.obj.requires
CMakeFiles/lib.dir/requires: CMakeFiles/lib.dir/src/lib/my_putchar.c.obj.requires

.PHONY : CMakeFiles/lib.dir/requires

CMakeFiles/lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lib.dir\cmake_clean.cmake
.PHONY : CMakeFiles/lib.dir/clean

CMakeFiles/lib.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\AMO\Desktop\BomberMan\bfm\CLION C:\Users\AMO\Desktop\BomberMan\bfm\CLION C:\Users\AMO\Desktop\BomberMan\bfm\CLION\cmake-build-debug C:\Users\AMO\Desktop\BomberMan\bfm\CLION\cmake-build-debug C:\Users\AMO\Desktop\BomberMan\bfm\CLION\cmake-build-debug\CMakeFiles\lib.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lib.dir/depend

