# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/qs4617/Arm/arm11_47/src/assemble

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/qs4617/Arm/arm11_47/src/assemble

# Include any dependencies generated for this target.
include CMakeFiles/assemble.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/assemble.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/assemble.dir/flags.make

CMakeFiles/assemble.dir/assemble.c.o: CMakeFiles/assemble.dir/flags.make
CMakeFiles/assemble.dir/assemble.c.o: assemble.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/qs4617/Arm/arm11_47/src/assemble/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/assemble.dir/assemble.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/assemble.dir/assemble.c.o   -c /homes/qs4617/Arm/arm11_47/src/assemble/assemble.c

CMakeFiles/assemble.dir/assemble.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assemble.dir/assemble.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/qs4617/Arm/arm11_47/src/assemble/assemble.c > CMakeFiles/assemble.dir/assemble.c.i

CMakeFiles/assemble.dir/assemble.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assemble.dir/assemble.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/qs4617/Arm/arm11_47/src/assemble/assemble.c -o CMakeFiles/assemble.dir/assemble.c.s

CMakeFiles/assemble.dir/assemble.c.o.requires:

.PHONY : CMakeFiles/assemble.dir/assemble.c.o.requires

CMakeFiles/assemble.dir/assemble.c.o.provides: CMakeFiles/assemble.dir/assemble.c.o.requires
	$(MAKE) -f CMakeFiles/assemble.dir/build.make CMakeFiles/assemble.dir/assemble.c.o.provides.build
.PHONY : CMakeFiles/assemble.dir/assemble.c.o.provides

CMakeFiles/assemble.dir/assemble.c.o.provides.build: CMakeFiles/assemble.dir/assemble.c.o


CMakeFiles/assemble.dir/list.c.o: CMakeFiles/assemble.dir/flags.make
CMakeFiles/assemble.dir/list.c.o: list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/qs4617/Arm/arm11_47/src/assemble/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/assemble.dir/list.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/assemble.dir/list.c.o   -c /homes/qs4617/Arm/arm11_47/src/assemble/list.c

CMakeFiles/assemble.dir/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assemble.dir/list.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/qs4617/Arm/arm11_47/src/assemble/list.c > CMakeFiles/assemble.dir/list.c.i

CMakeFiles/assemble.dir/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assemble.dir/list.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/qs4617/Arm/arm11_47/src/assemble/list.c -o CMakeFiles/assemble.dir/list.c.s

CMakeFiles/assemble.dir/list.c.o.requires:

.PHONY : CMakeFiles/assemble.dir/list.c.o.requires

CMakeFiles/assemble.dir/list.c.o.provides: CMakeFiles/assemble.dir/list.c.o.requires
	$(MAKE) -f CMakeFiles/assemble.dir/build.make CMakeFiles/assemble.dir/list.c.o.provides.build
.PHONY : CMakeFiles/assemble.dir/list.c.o.provides

CMakeFiles/assemble.dir/list.c.o.provides.build: CMakeFiles/assemble.dir/list.c.o


CMakeFiles/assemble.dir/binary_file_writer.c.o: CMakeFiles/assemble.dir/flags.make
CMakeFiles/assemble.dir/binary_file_writer.c.o: binary_file_writer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/qs4617/Arm/arm11_47/src/assemble/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/assemble.dir/binary_file_writer.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/assemble.dir/binary_file_writer.c.o   -c /homes/qs4617/Arm/arm11_47/src/assemble/binary_file_writer.c

CMakeFiles/assemble.dir/binary_file_writer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assemble.dir/binary_file_writer.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/qs4617/Arm/arm11_47/src/assemble/binary_file_writer.c > CMakeFiles/assemble.dir/binary_file_writer.c.i

CMakeFiles/assemble.dir/binary_file_writer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assemble.dir/binary_file_writer.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/qs4617/Arm/arm11_47/src/assemble/binary_file_writer.c -o CMakeFiles/assemble.dir/binary_file_writer.c.s

CMakeFiles/assemble.dir/binary_file_writer.c.o.requires:

.PHONY : CMakeFiles/assemble.dir/binary_file_writer.c.o.requires

CMakeFiles/assemble.dir/binary_file_writer.c.o.provides: CMakeFiles/assemble.dir/binary_file_writer.c.o.requires
	$(MAKE) -f CMakeFiles/assemble.dir/build.make CMakeFiles/assemble.dir/binary_file_writer.c.o.provides.build
.PHONY : CMakeFiles/assemble.dir/binary_file_writer.c.o.provides

CMakeFiles/assemble.dir/binary_file_writer.c.o.provides.build: CMakeFiles/assemble.dir/binary_file_writer.c.o


CMakeFiles/assemble.dir/tokenizer.c.o: CMakeFiles/assemble.dir/flags.make
CMakeFiles/assemble.dir/tokenizer.c.o: tokenizer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/qs4617/Arm/arm11_47/src/assemble/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/assemble.dir/tokenizer.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/assemble.dir/tokenizer.c.o   -c /homes/qs4617/Arm/arm11_47/src/assemble/tokenizer.c

CMakeFiles/assemble.dir/tokenizer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assemble.dir/tokenizer.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/qs4617/Arm/arm11_47/src/assemble/tokenizer.c > CMakeFiles/assemble.dir/tokenizer.c.i

CMakeFiles/assemble.dir/tokenizer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assemble.dir/tokenizer.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/qs4617/Arm/arm11_47/src/assemble/tokenizer.c -o CMakeFiles/assemble.dir/tokenizer.c.s

CMakeFiles/assemble.dir/tokenizer.c.o.requires:

.PHONY : CMakeFiles/assemble.dir/tokenizer.c.o.requires

CMakeFiles/assemble.dir/tokenizer.c.o.provides: CMakeFiles/assemble.dir/tokenizer.c.o.requires
	$(MAKE) -f CMakeFiles/assemble.dir/build.make CMakeFiles/assemble.dir/tokenizer.c.o.provides.build
.PHONY : CMakeFiles/assemble.dir/tokenizer.c.o.provides

CMakeFiles/assemble.dir/tokenizer.c.o.provides.build: CMakeFiles/assemble.dir/tokenizer.c.o


CMakeFiles/assemble.dir/symbol_table.c.o: CMakeFiles/assemble.dir/flags.make
CMakeFiles/assemble.dir/symbol_table.c.o: symbol_table.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/qs4617/Arm/arm11_47/src/assemble/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/assemble.dir/symbol_table.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/assemble.dir/symbol_table.c.o   -c /homes/qs4617/Arm/arm11_47/src/assemble/symbol_table.c

CMakeFiles/assemble.dir/symbol_table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assemble.dir/symbol_table.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/qs4617/Arm/arm11_47/src/assemble/symbol_table.c > CMakeFiles/assemble.dir/symbol_table.c.i

CMakeFiles/assemble.dir/symbol_table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assemble.dir/symbol_table.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/qs4617/Arm/arm11_47/src/assemble/symbol_table.c -o CMakeFiles/assemble.dir/symbol_table.c.s

CMakeFiles/assemble.dir/symbol_table.c.o.requires:

.PHONY : CMakeFiles/assemble.dir/symbol_table.c.o.requires

CMakeFiles/assemble.dir/symbol_table.c.o.provides: CMakeFiles/assemble.dir/symbol_table.c.o.requires
	$(MAKE) -f CMakeFiles/assemble.dir/build.make CMakeFiles/assemble.dir/symbol_table.c.o.provides.build
.PHONY : CMakeFiles/assemble.dir/symbol_table.c.o.provides

CMakeFiles/assemble.dir/symbol_table.c.o.provides.build: CMakeFiles/assemble.dir/symbol_table.c.o


# Object files for target assemble
assemble_OBJECTS = \
"CMakeFiles/assemble.dir/assemble.c.o" \
"CMakeFiles/assemble.dir/list.c.o" \
"CMakeFiles/assemble.dir/binary_file_writer.c.o" \
"CMakeFiles/assemble.dir/tokenizer.c.o" \
"CMakeFiles/assemble.dir/symbol_table.c.o"

# External object files for target assemble
assemble_EXTERNAL_OBJECTS =

assemble: CMakeFiles/assemble.dir/assemble.c.o
assemble: CMakeFiles/assemble.dir/list.c.o
assemble: CMakeFiles/assemble.dir/binary_file_writer.c.o
assemble: CMakeFiles/assemble.dir/tokenizer.c.o
assemble: CMakeFiles/assemble.dir/symbol_table.c.o
assemble: CMakeFiles/assemble.dir/build.make
assemble: CMakeFiles/assemble.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/qs4617/Arm/arm11_47/src/assemble/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable assemble"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/assemble.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/assemble.dir/build: assemble

.PHONY : CMakeFiles/assemble.dir/build

CMakeFiles/assemble.dir/requires: CMakeFiles/assemble.dir/assemble.c.o.requires
CMakeFiles/assemble.dir/requires: CMakeFiles/assemble.dir/list.c.o.requires
CMakeFiles/assemble.dir/requires: CMakeFiles/assemble.dir/binary_file_writer.c.o.requires
CMakeFiles/assemble.dir/requires: CMakeFiles/assemble.dir/tokenizer.c.o.requires
CMakeFiles/assemble.dir/requires: CMakeFiles/assemble.dir/symbol_table.c.o.requires

.PHONY : CMakeFiles/assemble.dir/requires

CMakeFiles/assemble.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/assemble.dir/cmake_clean.cmake
.PHONY : CMakeFiles/assemble.dir/clean

CMakeFiles/assemble.dir/depend:
	cd /homes/qs4617/Arm/arm11_47/src/assemble && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/qs4617/Arm/arm11_47/src/assemble /homes/qs4617/Arm/arm11_47/src/assemble /homes/qs4617/Arm/arm11_47/src/assemble /homes/qs4617/Arm/arm11_47/src/assemble /homes/qs4617/Arm/arm11_47/src/assemble/CMakeFiles/assemble.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/assemble.dir/depend

