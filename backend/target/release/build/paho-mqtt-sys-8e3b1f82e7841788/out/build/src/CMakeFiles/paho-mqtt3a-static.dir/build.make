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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build

# Include any dependencies generated for this target.
include src/CMakeFiles/paho-mqtt3a-static.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/paho-mqtt3a-static.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/paho-mqtt3a-static.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/paho-mqtt3a-static.dir/flags.make

src/CMakeFiles/paho-mqtt3a-static.dir/codegen:
.PHONY : src/CMakeFiles/paho-mqtt3a-static.dir/codegen

src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.o: src/CMakeFiles/paho-mqtt3a-static.dir/flags.make
src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.o: /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src/MQTTAsync.c
src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.o: src/CMakeFiles/paho-mqtt3a-static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.o"
	cd /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.o -MF CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.o.d -o CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.o -c /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src/MQTTAsync.c

src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.i"
	cd /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src/MQTTAsync.c > CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.i

src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.s"
	cd /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src/MQTTAsync.c -o CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.s

src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.o: src/CMakeFiles/paho-mqtt3a-static.dir/flags.make
src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.o: /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src/MQTTAsyncUtils.c
src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.o: src/CMakeFiles/paho-mqtt3a-static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.o"
	cd /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.o -MF CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.o.d -o CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.o -c /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src/MQTTAsyncUtils.c

src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.i"
	cd /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src/MQTTAsyncUtils.c > CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.i

src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.s"
	cd /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src/MQTTAsyncUtils.c -o CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.s

# Object files for target paho-mqtt3a-static
paho__mqtt3a__static_OBJECTS = \
"CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.o" \
"CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.o"

# External object files for target paho-mqtt3a-static
paho__mqtt3a__static_EXTERNAL_OBJECTS = \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/MQTTTime.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/MQTTProtocolClient.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/Clients.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/utf-8.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/MQTTPacket.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/MQTTPacketOut.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/Messages.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/Tree.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/Socket.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/Log.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/MQTTPersistence.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/Thread.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/MQTTProtocolOut.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/MQTTPersistenceDefault.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/SocketBuffer.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/LinkedList.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/MQTTProperties.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/MQTTReasonCodes.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/Base64.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/SHA1.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/WebSocket.c.o" \
"/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/common_obj_static.dir/Proxy.c.o"

src/libpaho-mqtt3a.a: src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsync.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/paho-mqtt3a-static.dir/MQTTAsyncUtils.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/MQTTTime.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/MQTTProtocolClient.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/Clients.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/utf-8.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/MQTTPacket.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/MQTTPacketOut.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/Messages.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/Tree.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/Socket.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/Log.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/MQTTPersistence.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/Thread.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/MQTTProtocolOut.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/MQTTPersistenceDefault.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/SocketBuffer.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/LinkedList.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/MQTTProperties.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/MQTTReasonCodes.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/Base64.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/SHA1.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/WebSocket.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/common_obj_static.dir/Proxy.c.o
src/libpaho-mqtt3a.a: src/CMakeFiles/paho-mqtt3a-static.dir/build.make
src/libpaho-mqtt3a.a: src/CMakeFiles/paho-mqtt3a-static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libpaho-mqtt3a.a"
	cd /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src && $(CMAKE_COMMAND) -P CMakeFiles/paho-mqtt3a-static.dir/cmake_clean_target.cmake
	cd /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/paho-mqtt3a-static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/paho-mqtt3a-static.dir/build: src/libpaho-mqtt3a.a
.PHONY : src/CMakeFiles/paho-mqtt3a-static.dir/build

src/CMakeFiles/paho-mqtt3a-static.dir/clean:
	cd /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src && $(CMAKE_COMMAND) -P CMakeFiles/paho-mqtt3a-static.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/paho-mqtt3a-static.dir/clean

src/CMakeFiles/paho-mqtt3a-static.dir/depend:
	cd /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src /Users/benediktillich/repos/WiseRiders/backend/target/release/build/paho-mqtt-sys-8e3b1f82e7841788/out/build/src/CMakeFiles/paho-mqtt3a-static.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/paho-mqtt3a-static.dir/depend

