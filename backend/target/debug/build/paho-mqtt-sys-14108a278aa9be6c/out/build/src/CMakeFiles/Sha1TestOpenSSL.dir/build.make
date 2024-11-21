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
CMAKE_BINARY_DIR = /Users/benediktillich/repos/uprotocol_backend/target/debug/build/paho-mqtt-sys-14108a278aa9be6c/out/build

# Include any dependencies generated for this target.
include src/CMakeFiles/Sha1TestOpenSSL.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/Sha1TestOpenSSL.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Sha1TestOpenSSL.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Sha1TestOpenSSL.dir/flags.make

src/CMakeFiles/Sha1TestOpenSSL.dir/codegen:
.PHONY : src/CMakeFiles/Sha1TestOpenSSL.dir/codegen

src/CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.o: src/CMakeFiles/Sha1TestOpenSSL.dir/flags.make
src/CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.o: /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src/SHA1.c
src/CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.o: src/CMakeFiles/Sha1TestOpenSSL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/benediktillich/repos/uprotocol_backend/target/debug/build/paho-mqtt-sys-14108a278aa9be6c/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.o"
	cd /Users/benediktillich/repos/uprotocol_backend/target/debug/build/paho-mqtt-sys-14108a278aa9be6c/out/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.o -MF CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.o.d -o CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.o -c /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src/SHA1.c

src/CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.i"
	cd /Users/benediktillich/repos/uprotocol_backend/target/debug/build/paho-mqtt-sys-14108a278aa9be6c/out/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src/SHA1.c > CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.i

src/CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.s"
	cd /Users/benediktillich/repos/uprotocol_backend/target/debug/build/paho-mqtt-sys-14108a278aa9be6c/out/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src/SHA1.c -o CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.s

# Object files for target Sha1TestOpenSSL
Sha1TestOpenSSL_OBJECTS = \
"CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.o"

# External object files for target Sha1TestOpenSSL
Sha1TestOpenSSL_EXTERNAL_OBJECTS =

src/Sha1TestOpenSSL: src/CMakeFiles/Sha1TestOpenSSL.dir/SHA1.c.o
src/Sha1TestOpenSSL: src/CMakeFiles/Sha1TestOpenSSL.dir/build.make
src/Sha1TestOpenSSL: /Users/benediktillich/repos/uprotocol_backend/target/debug/build/openssl-sys-e7fe0ca43362dd57/out/openssl-build/install/lib/libssl.a
src/Sha1TestOpenSSL: /Users/benediktillich/repos/uprotocol_backend/target/debug/build/openssl-sys-e7fe0ca43362dd57/out/openssl-build/install/lib/libcrypto.a
src/Sha1TestOpenSSL: src/CMakeFiles/Sha1TestOpenSSL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/benediktillich/repos/uprotocol_backend/target/debug/build/paho-mqtt-sys-14108a278aa9be6c/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Sha1TestOpenSSL"
	cd /Users/benediktillich/repos/uprotocol_backend/target/debug/build/paho-mqtt-sys-14108a278aa9be6c/out/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Sha1TestOpenSSL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/Sha1TestOpenSSL.dir/build: src/Sha1TestOpenSSL
.PHONY : src/CMakeFiles/Sha1TestOpenSSL.dir/build

src/CMakeFiles/Sha1TestOpenSSL.dir/clean:
	cd /Users/benediktillich/repos/uprotocol_backend/target/debug/build/paho-mqtt-sys-14108a278aa9be6c/out/build/src && $(CMAKE_COMMAND) -P CMakeFiles/Sha1TestOpenSSL.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/Sha1TestOpenSSL.dir/clean

src/CMakeFiles/Sha1TestOpenSSL.dir/depend:
	cd /Users/benediktillich/repos/uprotocol_backend/target/debug/build/paho-mqtt-sys-14108a278aa9be6c/out/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c /Users/benediktillich/.cargo/registry/src/index.crates.io-6f17d22bba15001f/paho-mqtt-sys-0.9.0/paho.mqtt.c/src /Users/benediktillich/repos/uprotocol_backend/target/debug/build/paho-mqtt-sys-14108a278aa9be6c/out/build /Users/benediktillich/repos/uprotocol_backend/target/debug/build/paho-mqtt-sys-14108a278aa9be6c/out/build/src /Users/benediktillich/repos/uprotocol_backend/target/debug/build/paho-mqtt-sys-14108a278aa9be6c/out/build/src/CMakeFiles/Sha1TestOpenSSL.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/Sha1TestOpenSSL.dir/depend

