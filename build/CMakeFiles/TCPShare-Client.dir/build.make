# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Nix0712/Project/TCPShare

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Nix0712/Project/TCPShare/build

# Include any dependencies generated for this target.
include CMakeFiles/TCPShare-Client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TCPShare-Client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TCPShare-Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TCPShare-Client.dir/flags.make

CMakeFiles/TCPShare-Client.dir/codegen:
.PHONY : CMakeFiles/TCPShare-Client.dir/codegen

CMakeFiles/TCPShare-Client.dir/src/client.cpp.o: CMakeFiles/TCPShare-Client.dir/flags.make
CMakeFiles/TCPShare-Client.dir/src/client.cpp.o: /home/Nix0712/Project/TCPShare/src/client.cpp
CMakeFiles/TCPShare-Client.dir/src/client.cpp.o: CMakeFiles/TCPShare-Client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/Nix0712/Project/TCPShare/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TCPShare-Client.dir/src/client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TCPShare-Client.dir/src/client.cpp.o -MF CMakeFiles/TCPShare-Client.dir/src/client.cpp.o.d -o CMakeFiles/TCPShare-Client.dir/src/client.cpp.o -c /home/Nix0712/Project/TCPShare/src/client.cpp

CMakeFiles/TCPShare-Client.dir/src/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TCPShare-Client.dir/src/client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Nix0712/Project/TCPShare/src/client.cpp > CMakeFiles/TCPShare-Client.dir/src/client.cpp.i

CMakeFiles/TCPShare-Client.dir/src/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TCPShare-Client.dir/src/client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Nix0712/Project/TCPShare/src/client.cpp -o CMakeFiles/TCPShare-Client.dir/src/client.cpp.s

# Object files for target TCPShare-Client
TCPShare__Client_OBJECTS = \
"CMakeFiles/TCPShare-Client.dir/src/client.cpp.o"

# External object files for target TCPShare-Client
TCPShare__Client_EXTERNAL_OBJECTS =

TCPShare-Client: CMakeFiles/TCPShare-Client.dir/src/client.cpp.o
TCPShare-Client: CMakeFiles/TCPShare-Client.dir/build.make
TCPShare-Client: CMakeFiles/TCPShare-Client.dir/compiler_depend.ts
TCPShare-Client: CMakeFiles/TCPShare-Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/Nix0712/Project/TCPShare/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TCPShare-Client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TCPShare-Client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TCPShare-Client.dir/build: TCPShare-Client
.PHONY : CMakeFiles/TCPShare-Client.dir/build

CMakeFiles/TCPShare-Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TCPShare-Client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TCPShare-Client.dir/clean

CMakeFiles/TCPShare-Client.dir/depend:
	cd /home/Nix0712/Project/TCPShare/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Nix0712/Project/TCPShare /home/Nix0712/Project/TCPShare /home/Nix0712/Project/TCPShare/build /home/Nix0712/Project/TCPShare/build /home/Nix0712/Project/TCPShare/build/CMakeFiles/TCPShare-Client.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/TCPShare-Client.dir/depend

