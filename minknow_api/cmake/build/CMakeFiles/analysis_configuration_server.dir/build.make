# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.22.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.22.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/brianzhang/Documents/grpc/examples/cpp/minknow_api

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/brianzhang/Documents/grpc/examples/cpp/minknow_api/cmake/build

# Include any dependencies generated for this target.
include CMakeFiles/analysis_configuration_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/analysis_configuration_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/analysis_configuration_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/analysis_configuration_server.dir/flags.make

CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.o: CMakeFiles/analysis_configuration_server.dir/flags.make
CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.o: ../../analysis_configuration_server.cc
CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.o: CMakeFiles/analysis_configuration_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/brianzhang/Documents/grpc/examples/cpp/minknow_api/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.o -MF CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.o.d -o CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.o -c /Users/brianzhang/Documents/grpc/examples/cpp/minknow_api/analysis_configuration_server.cc

CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/brianzhang/Documents/grpc/examples/cpp/minknow_api/analysis_configuration_server.cc > CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.i

CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/brianzhang/Documents/grpc/examples/cpp/minknow_api/analysis_configuration_server.cc -o CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.s

# Object files for target analysis_configuration_server
analysis_configuration_server_OBJECTS = \
"CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.o"

# External object files for target analysis_configuration_server
analysis_configuration_server_EXTERNAL_OBJECTS =

analysis_configuration_server: CMakeFiles/analysis_configuration_server.dir/analysis_configuration_server.cc.o
analysis_configuration_server: CMakeFiles/analysis_configuration_server.dir/build.make
analysis_configuration_server: librg_grpc_proto.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libgrpc++_reflection.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libgrpc++.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libprotobuf.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libgrpc.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libz.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libcares.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libaddress_sorting.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libre2.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_raw_hash_set.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_hashtablez_sampler.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_exponential_biased.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_hash.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_city.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_wyhash.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_statusor.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_bad_variant_access.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libgpr.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libupb.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_status.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_cord.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_bad_optional_access.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_str_format_internal.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_synchronization.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_stacktrace.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_symbolize.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_debugging_internal.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_demangle_internal.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_graphcycles_internal.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_malloc_internal.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_time.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_strings.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_throw_delegate.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_int128.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_strings_internal.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_base.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_raw_logging_internal.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_log_severity.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_spinlock_wait.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_civil_time.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libabsl_time_zone.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libssl.a
analysis_configuration_server: /Users/brianzhang/.local/lib/libcrypto.a
analysis_configuration_server: CMakeFiles/analysis_configuration_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/brianzhang/Documents/grpc/examples/cpp/minknow_api/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable analysis_configuration_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/analysis_configuration_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/analysis_configuration_server.dir/build: analysis_configuration_server
.PHONY : CMakeFiles/analysis_configuration_server.dir/build

CMakeFiles/analysis_configuration_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/analysis_configuration_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/analysis_configuration_server.dir/clean

CMakeFiles/analysis_configuration_server.dir/depend:
	cd /Users/brianzhang/Documents/grpc/examples/cpp/minknow_api/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/brianzhang/Documents/grpc/examples/cpp/minknow_api /Users/brianzhang/Documents/grpc/examples/cpp/minknow_api /Users/brianzhang/Documents/grpc/examples/cpp/minknow_api/cmake/build /Users/brianzhang/Documents/grpc/examples/cpp/minknow_api/cmake/build /Users/brianzhang/Documents/grpc/examples/cpp/minknow_api/cmake/build/CMakeFiles/analysis_configuration_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/analysis_configuration_server.dir/depend

