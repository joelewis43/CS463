# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/devingendron/Coding/CS467/CS463

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/devingendron/Coding/CS467/CS463/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CS463.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CS463.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CS463.dir/flags.make

CMakeFiles/CS463.dir/lib/city.cpp.o: CMakeFiles/CS463.dir/flags.make
CMakeFiles/CS463.dir/lib/city.cpp.o: ../lib/city.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CS463.dir/lib/city.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CS463.dir/lib/city.cpp.o -c /Users/devingendron/Coding/CS467/CS463/lib/city.cpp

CMakeFiles/CS463.dir/lib/city.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS463.dir/lib/city.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/devingendron/Coding/CS467/CS463/lib/city.cpp > CMakeFiles/CS463.dir/lib/city.cpp.i

CMakeFiles/CS463.dir/lib/city.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS463.dir/lib/city.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/devingendron/Coding/CS467/CS463/lib/city.cpp -o CMakeFiles/CS463.dir/lib/city.cpp.s

CMakeFiles/CS463.dir/lib/clientSocket.cpp.o: CMakeFiles/CS463.dir/flags.make
CMakeFiles/CS463.dir/lib/clientSocket.cpp.o: ../lib/clientSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CS463.dir/lib/clientSocket.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CS463.dir/lib/clientSocket.cpp.o -c /Users/devingendron/Coding/CS467/CS463/lib/clientSocket.cpp

CMakeFiles/CS463.dir/lib/clientSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS463.dir/lib/clientSocket.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/devingendron/Coding/CS467/CS463/lib/clientSocket.cpp > CMakeFiles/CS463.dir/lib/clientSocket.cpp.i

CMakeFiles/CS463.dir/lib/clientSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS463.dir/lib/clientSocket.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/devingendron/Coding/CS467/CS463/lib/clientSocket.cpp -o CMakeFiles/CS463.dir/lib/clientSocket.cpp.s

CMakeFiles/CS463.dir/lib/environment.cpp.o: CMakeFiles/CS463.dir/flags.make
CMakeFiles/CS463.dir/lib/environment.cpp.o: ../lib/environment.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CS463.dir/lib/environment.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CS463.dir/lib/environment.cpp.o -c /Users/devingendron/Coding/CS467/CS463/lib/environment.cpp

CMakeFiles/CS463.dir/lib/environment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS463.dir/lib/environment.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/devingendron/Coding/CS467/CS463/lib/environment.cpp > CMakeFiles/CS463.dir/lib/environment.cpp.i

CMakeFiles/CS463.dir/lib/environment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS463.dir/lib/environment.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/devingendron/Coding/CS467/CS463/lib/environment.cpp -o CMakeFiles/CS463.dir/lib/environment.cpp.s

CMakeFiles/CS463.dir/lib/GameControllerClient.cpp.o: CMakeFiles/CS463.dir/flags.make
CMakeFiles/CS463.dir/lib/GameControllerClient.cpp.o: ../lib/GameControllerClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/CS463.dir/lib/GameControllerClient.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CS463.dir/lib/GameControllerClient.cpp.o -c /Users/devingendron/Coding/CS467/CS463/lib/GameControllerClient.cpp

CMakeFiles/CS463.dir/lib/GameControllerClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS463.dir/lib/GameControllerClient.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/devingendron/Coding/CS467/CS463/lib/GameControllerClient.cpp > CMakeFiles/CS463.dir/lib/GameControllerClient.cpp.i

CMakeFiles/CS463.dir/lib/GameControllerClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS463.dir/lib/GameControllerClient.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/devingendron/Coding/CS467/CS463/lib/GameControllerClient.cpp -o CMakeFiles/CS463.dir/lib/GameControllerClient.cpp.s

CMakeFiles/CS463.dir/lib/GameControllerServer.cpp.o: CMakeFiles/CS463.dir/flags.make
CMakeFiles/CS463.dir/lib/GameControllerServer.cpp.o: ../lib/GameControllerServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/CS463.dir/lib/GameControllerServer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CS463.dir/lib/GameControllerServer.cpp.o -c /Users/devingendron/Coding/CS467/CS463/lib/GameControllerServer.cpp

CMakeFiles/CS463.dir/lib/GameControllerServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS463.dir/lib/GameControllerServer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/devingendron/Coding/CS467/CS463/lib/GameControllerServer.cpp > CMakeFiles/CS463.dir/lib/GameControllerServer.cpp.i

CMakeFiles/CS463.dir/lib/GameControllerServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS463.dir/lib/GameControllerServer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/devingendron/Coding/CS467/CS463/lib/GameControllerServer.cpp -o CMakeFiles/CS463.dir/lib/GameControllerServer.cpp.s

CMakeFiles/CS463.dir/lib/matrix.cpp.o: CMakeFiles/CS463.dir/flags.make
CMakeFiles/CS463.dir/lib/matrix.cpp.o: ../lib/matrix.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/CS463.dir/lib/matrix.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CS463.dir/lib/matrix.cpp.o -c /Users/devingendron/Coding/CS467/CS463/lib/matrix.cpp

CMakeFiles/CS463.dir/lib/matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS463.dir/lib/matrix.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/devingendron/Coding/CS467/CS463/lib/matrix.cpp > CMakeFiles/CS463.dir/lib/matrix.cpp.i

CMakeFiles/CS463.dir/lib/matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS463.dir/lib/matrix.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/devingendron/Coding/CS467/CS463/lib/matrix.cpp -o CMakeFiles/CS463.dir/lib/matrix.cpp.s

CMakeFiles/CS463.dir/lib/Player.cpp.o: CMakeFiles/CS463.dir/flags.make
CMakeFiles/CS463.dir/lib/Player.cpp.o: ../lib/Player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/CS463.dir/lib/Player.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CS463.dir/lib/Player.cpp.o -c /Users/devingendron/Coding/CS467/CS463/lib/Player.cpp

CMakeFiles/CS463.dir/lib/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS463.dir/lib/Player.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/devingendron/Coding/CS467/CS463/lib/Player.cpp > CMakeFiles/CS463.dir/lib/Player.cpp.i

CMakeFiles/CS463.dir/lib/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS463.dir/lib/Player.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/devingendron/Coding/CS467/CS463/lib/Player.cpp -o CMakeFiles/CS463.dir/lib/Player.cpp.s

CMakeFiles/CS463.dir/lib/random.cpp.o: CMakeFiles/CS463.dir/flags.make
CMakeFiles/CS463.dir/lib/random.cpp.o: ../lib/random.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/CS463.dir/lib/random.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CS463.dir/lib/random.cpp.o -c /Users/devingendron/Coding/CS467/CS463/lib/random.cpp

CMakeFiles/CS463.dir/lib/random.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS463.dir/lib/random.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/devingendron/Coding/CS467/CS463/lib/random.cpp > CMakeFiles/CS463.dir/lib/random.cpp.i

CMakeFiles/CS463.dir/lib/random.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS463.dir/lib/random.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/devingendron/Coding/CS467/CS463/lib/random.cpp -o CMakeFiles/CS463.dir/lib/random.cpp.s

CMakeFiles/CS463.dir/lib/serverSocket.cpp.o: CMakeFiles/CS463.dir/flags.make
CMakeFiles/CS463.dir/lib/serverSocket.cpp.o: ../lib/serverSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/CS463.dir/lib/serverSocket.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CS463.dir/lib/serverSocket.cpp.o -c /Users/devingendron/Coding/CS467/CS463/lib/serverSocket.cpp

CMakeFiles/CS463.dir/lib/serverSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS463.dir/lib/serverSocket.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/devingendron/Coding/CS467/CS463/lib/serverSocket.cpp > CMakeFiles/CS463.dir/lib/serverSocket.cpp.i

CMakeFiles/CS463.dir/lib/serverSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS463.dir/lib/serverSocket.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/devingendron/Coding/CS467/CS463/lib/serverSocket.cpp -o CMakeFiles/CS463.dir/lib/serverSocket.cpp.s

CMakeFiles/CS463.dir/lib/window.cpp.o: CMakeFiles/CS463.dir/flags.make
CMakeFiles/CS463.dir/lib/window.cpp.o: ../lib/window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/CS463.dir/lib/window.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CS463.dir/lib/window.cpp.o -c /Users/devingendron/Coding/CS467/CS463/lib/window.cpp

CMakeFiles/CS463.dir/lib/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS463.dir/lib/window.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/devingendron/Coding/CS467/CS463/lib/window.cpp > CMakeFiles/CS463.dir/lib/window.cpp.i

CMakeFiles/CS463.dir/lib/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS463.dir/lib/window.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/devingendron/Coding/CS467/CS463/lib/window.cpp -o CMakeFiles/CS463.dir/lib/window.cpp.s

CMakeFiles/CS463.dir/client.cpp.o: CMakeFiles/CS463.dir/flags.make
CMakeFiles/CS463.dir/client.cpp.o: ../client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/CS463.dir/client.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CS463.dir/client.cpp.o -c /Users/devingendron/Coding/CS467/CS463/client.cpp

CMakeFiles/CS463.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS463.dir/client.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/devingendron/Coding/CS467/CS463/client.cpp > CMakeFiles/CS463.dir/client.cpp.i

CMakeFiles/CS463.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS463.dir/client.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/devingendron/Coding/CS467/CS463/client.cpp -o CMakeFiles/CS463.dir/client.cpp.s

CMakeFiles/CS463.dir/server.cpp.o: CMakeFiles/CS463.dir/flags.make
CMakeFiles/CS463.dir/server.cpp.o: ../server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/CS463.dir/server.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CS463.dir/server.cpp.o -c /Users/devingendron/Coding/CS467/CS463/server.cpp

CMakeFiles/CS463.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CS463.dir/server.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/devingendron/Coding/CS467/CS463/server.cpp > CMakeFiles/CS463.dir/server.cpp.i

CMakeFiles/CS463.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CS463.dir/server.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/devingendron/Coding/CS467/CS463/server.cpp -o CMakeFiles/CS463.dir/server.cpp.s

# Object files for target CS463
CS463_OBJECTS = \
"CMakeFiles/CS463.dir/lib/city.cpp.o" \
"CMakeFiles/CS463.dir/lib/clientSocket.cpp.o" \
"CMakeFiles/CS463.dir/lib/environment.cpp.o" \
"CMakeFiles/CS463.dir/lib/GameControllerClient.cpp.o" \
"CMakeFiles/CS463.dir/lib/GameControllerServer.cpp.o" \
"CMakeFiles/CS463.dir/lib/matrix.cpp.o" \
"CMakeFiles/CS463.dir/lib/Player.cpp.o" \
"CMakeFiles/CS463.dir/lib/random.cpp.o" \
"CMakeFiles/CS463.dir/lib/serverSocket.cpp.o" \
"CMakeFiles/CS463.dir/lib/window.cpp.o" \
"CMakeFiles/CS463.dir/client.cpp.o" \
"CMakeFiles/CS463.dir/server.cpp.o"

# External object files for target CS463
CS463_EXTERNAL_OBJECTS =

CS463: CMakeFiles/CS463.dir/lib/city.cpp.o
CS463: CMakeFiles/CS463.dir/lib/clientSocket.cpp.o
CS463: CMakeFiles/CS463.dir/lib/environment.cpp.o
CS463: CMakeFiles/CS463.dir/lib/GameControllerClient.cpp.o
CS463: CMakeFiles/CS463.dir/lib/GameControllerServer.cpp.o
CS463: CMakeFiles/CS463.dir/lib/matrix.cpp.o
CS463: CMakeFiles/CS463.dir/lib/Player.cpp.o
CS463: CMakeFiles/CS463.dir/lib/random.cpp.o
CS463: CMakeFiles/CS463.dir/lib/serverSocket.cpp.o
CS463: CMakeFiles/CS463.dir/lib/window.cpp.o
CS463: CMakeFiles/CS463.dir/client.cpp.o
CS463: CMakeFiles/CS463.dir/server.cpp.o
CS463: CMakeFiles/CS463.dir/build.make
CS463: CMakeFiles/CS463.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable CS463"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CS463.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CS463.dir/build: CS463

.PHONY : CMakeFiles/CS463.dir/build

CMakeFiles/CS463.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CS463.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CS463.dir/clean

CMakeFiles/CS463.dir/depend:
	cd /Users/devingendron/Coding/CS467/CS463/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/devingendron/Coding/CS467/CS463 /Users/devingendron/Coding/CS467/CS463 /Users/devingendron/Coding/CS467/CS463/cmake-build-debug /Users/devingendron/Coding/CS467/CS463/cmake-build-debug /Users/devingendron/Coding/CS467/CS463/cmake-build-debug/CMakeFiles/CS463.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CS463.dir/depend

