# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cyruspellet/Desktop/XCoin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cyruspellet/Desktop/XCoin/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/xcoin.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/xcoin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/xcoin.dir/flags.make

CMakeFiles/xcoin.dir/main.cpp.o: CMakeFiles/xcoin.dir/flags.make
CMakeFiles/xcoin.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cyruspellet/Desktop/XCoin/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/xcoin.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xcoin.dir/main.cpp.o -c /Users/cyruspellet/Desktop/XCoin/main.cpp

CMakeFiles/xcoin.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xcoin.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cyruspellet/Desktop/XCoin/main.cpp > CMakeFiles/xcoin.dir/main.cpp.i

CMakeFiles/xcoin.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xcoin.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cyruspellet/Desktop/XCoin/main.cpp -o CMakeFiles/xcoin.dir/main.cpp.s

CMakeFiles/xcoin.dir/XBlockchain/block.cpp.o: CMakeFiles/xcoin.dir/flags.make
CMakeFiles/xcoin.dir/XBlockchain/block.cpp.o: ../XBlockchain/block.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cyruspellet/Desktop/XCoin/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/xcoin.dir/XBlockchain/block.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xcoin.dir/XBlockchain/block.cpp.o -c /Users/cyruspellet/Desktop/XCoin/XBlockchain/block.cpp

CMakeFiles/xcoin.dir/XBlockchain/block.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xcoin.dir/XBlockchain/block.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cyruspellet/Desktop/XCoin/XBlockchain/block.cpp > CMakeFiles/xcoin.dir/XBlockchain/block.cpp.i

CMakeFiles/xcoin.dir/XBlockchain/block.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xcoin.dir/XBlockchain/block.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cyruspellet/Desktop/XCoin/XBlockchain/block.cpp -o CMakeFiles/xcoin.dir/XBlockchain/block.cpp.s

CMakeFiles/xcoin.dir/XBlockchain/Blockchain.cpp.o: CMakeFiles/xcoin.dir/flags.make
CMakeFiles/xcoin.dir/XBlockchain/Blockchain.cpp.o: ../XBlockchain/Blockchain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cyruspellet/Desktop/XCoin/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/xcoin.dir/XBlockchain/Blockchain.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xcoin.dir/XBlockchain/Blockchain.cpp.o -c /Users/cyruspellet/Desktop/XCoin/XBlockchain/Blockchain.cpp

CMakeFiles/xcoin.dir/XBlockchain/Blockchain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xcoin.dir/XBlockchain/Blockchain.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cyruspellet/Desktop/XCoin/XBlockchain/Blockchain.cpp > CMakeFiles/xcoin.dir/XBlockchain/Blockchain.cpp.i

CMakeFiles/xcoin.dir/XBlockchain/Blockchain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xcoin.dir/XBlockchain/Blockchain.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cyruspellet/Desktop/XCoin/XBlockchain/Blockchain.cpp -o CMakeFiles/xcoin.dir/XBlockchain/Blockchain.cpp.s

CMakeFiles/xcoin.dir/XBlockchain/sha256.cpp.o: CMakeFiles/xcoin.dir/flags.make
CMakeFiles/xcoin.dir/XBlockchain/sha256.cpp.o: ../XBlockchain/sha256.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cyruspellet/Desktop/XCoin/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/xcoin.dir/XBlockchain/sha256.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xcoin.dir/XBlockchain/sha256.cpp.o -c /Users/cyruspellet/Desktop/XCoin/XBlockchain/sha256.cpp

CMakeFiles/xcoin.dir/XBlockchain/sha256.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xcoin.dir/XBlockchain/sha256.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cyruspellet/Desktop/XCoin/XBlockchain/sha256.cpp > CMakeFiles/xcoin.dir/XBlockchain/sha256.cpp.i

CMakeFiles/xcoin.dir/XBlockchain/sha256.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xcoin.dir/XBlockchain/sha256.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cyruspellet/Desktop/XCoin/XBlockchain/sha256.cpp -o CMakeFiles/xcoin.dir/XBlockchain/sha256.cpp.s

CMakeFiles/xcoin.dir/XBlockchain/bignumber.cpp.o: CMakeFiles/xcoin.dir/flags.make
CMakeFiles/xcoin.dir/XBlockchain/bignumber.cpp.o: ../XBlockchain/bignumber.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cyruspellet/Desktop/XCoin/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/xcoin.dir/XBlockchain/bignumber.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xcoin.dir/XBlockchain/bignumber.cpp.o -c /Users/cyruspellet/Desktop/XCoin/XBlockchain/bignumber.cpp

CMakeFiles/xcoin.dir/XBlockchain/bignumber.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xcoin.dir/XBlockchain/bignumber.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cyruspellet/Desktop/XCoin/XBlockchain/bignumber.cpp > CMakeFiles/xcoin.dir/XBlockchain/bignumber.cpp.i

CMakeFiles/xcoin.dir/XBlockchain/bignumber.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xcoin.dir/XBlockchain/bignumber.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cyruspellet/Desktop/XCoin/XBlockchain/bignumber.cpp -o CMakeFiles/xcoin.dir/XBlockchain/bignumber.cpp.s

# Object files for target xcoin
xcoin_OBJECTS = \
"CMakeFiles/xcoin.dir/main.cpp.o" \
"CMakeFiles/xcoin.dir/XBlockchain/block.cpp.o" \
"CMakeFiles/xcoin.dir/XBlockchain/Blockchain.cpp.o" \
"CMakeFiles/xcoin.dir/XBlockchain/sha256.cpp.o" \
"CMakeFiles/xcoin.dir/XBlockchain/bignumber.cpp.o"

# External object files for target xcoin
xcoin_EXTERNAL_OBJECTS =

xcoin: CMakeFiles/xcoin.dir/main.cpp.o
xcoin: CMakeFiles/xcoin.dir/XBlockchain/block.cpp.o
xcoin: CMakeFiles/xcoin.dir/XBlockchain/Blockchain.cpp.o
xcoin: CMakeFiles/xcoin.dir/XBlockchain/sha256.cpp.o
xcoin: CMakeFiles/xcoin.dir/XBlockchain/bignumber.cpp.o
xcoin: CMakeFiles/xcoin.dir/build.make
xcoin: CMakeFiles/xcoin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/cyruspellet/Desktop/XCoin/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable xcoin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xcoin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/xcoin.dir/build: xcoin
.PHONY : CMakeFiles/xcoin.dir/build

CMakeFiles/xcoin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/xcoin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/xcoin.dir/clean

CMakeFiles/xcoin.dir/depend:
	cd /Users/cyruspellet/Desktop/XCoin/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cyruspellet/Desktop/XCoin /Users/cyruspellet/Desktop/XCoin /Users/cyruspellet/Desktop/XCoin/cmake-build-debug /Users/cyruspellet/Desktop/XCoin/cmake-build-debug /Users/cyruspellet/Desktop/XCoin/cmake-build-debug/CMakeFiles/xcoin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/xcoin.dir/depend

