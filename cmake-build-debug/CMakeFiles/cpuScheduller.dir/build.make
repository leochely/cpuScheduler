# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = "C:\Program Files (x86)\JetBrains\CLion 2018.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\JetBrains\CLion 2018.2.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = Z:\CS\CSCI442\cpuScheduller

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = Z:\CS\CSCI442\cpuScheduller\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cpuScheduller.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cpuScheduller.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpuScheduller.dir/flags.make

CMakeFiles/cpuScheduller.dir/main.cpp.obj: CMakeFiles/cpuScheduller.dir/flags.make
CMakeFiles/cpuScheduller.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=Z:\CS\CSCI442\cpuScheduller\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpuScheduller.dir/main.cpp.obj"
	C:\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpuScheduller.dir\main.cpp.obj -c Z:\CS\CSCI442\cpuScheduller\main.cpp

CMakeFiles/cpuScheduller.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpuScheduller.dir/main.cpp.i"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E Z:\CS\CSCI442\cpuScheduller\main.cpp > CMakeFiles\cpuScheduller.dir\main.cpp.i

CMakeFiles/cpuScheduller.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpuScheduller.dir/main.cpp.s"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S Z:\CS\CSCI442\cpuScheduller\main.cpp -o CMakeFiles\cpuScheduller.dir\main.cpp.s

CMakeFiles/cpuScheduller.dir/process.cpp.obj: CMakeFiles/cpuScheduller.dir/flags.make
CMakeFiles/cpuScheduller.dir/process.cpp.obj: ../process.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=Z:\CS\CSCI442\cpuScheduller\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cpuScheduller.dir/process.cpp.obj"
	C:\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpuScheduller.dir\process.cpp.obj -c Z:\CS\CSCI442\cpuScheduller\process.cpp

CMakeFiles/cpuScheduller.dir/process.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpuScheduller.dir/process.cpp.i"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E Z:\CS\CSCI442\cpuScheduller\process.cpp > CMakeFiles\cpuScheduller.dir\process.cpp.i

CMakeFiles/cpuScheduller.dir/process.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpuScheduller.dir/process.cpp.s"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S Z:\CS\CSCI442\cpuScheduller\process.cpp -o CMakeFiles\cpuScheduller.dir\process.cpp.s

CMakeFiles/cpuScheduller.dir/event.cpp.obj: CMakeFiles/cpuScheduller.dir/flags.make
CMakeFiles/cpuScheduller.dir/event.cpp.obj: ../event.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=Z:\CS\CSCI442\cpuScheduller\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cpuScheduller.dir/event.cpp.obj"
	C:\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpuScheduller.dir\event.cpp.obj -c Z:\CS\CSCI442\cpuScheduller\event.cpp

CMakeFiles/cpuScheduller.dir/event.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpuScheduller.dir/event.cpp.i"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E Z:\CS\CSCI442\cpuScheduller\event.cpp > CMakeFiles\cpuScheduller.dir\event.cpp.i

CMakeFiles/cpuScheduller.dir/event.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpuScheduller.dir/event.cpp.s"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S Z:\CS\CSCI442\cpuScheduller\event.cpp -o CMakeFiles\cpuScheduller.dir\event.cpp.s

CMakeFiles/cpuScheduller.dir/thread.cpp.obj: CMakeFiles/cpuScheduller.dir/flags.make
CMakeFiles/cpuScheduller.dir/thread.cpp.obj: ../thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=Z:\CS\CSCI442\cpuScheduller\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cpuScheduller.dir/thread.cpp.obj"
	C:\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpuScheduller.dir\thread.cpp.obj -c Z:\CS\CSCI442\cpuScheduller\thread.cpp

CMakeFiles/cpuScheduller.dir/thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpuScheduller.dir/thread.cpp.i"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E Z:\CS\CSCI442\cpuScheduller\thread.cpp > CMakeFiles\cpuScheduller.dir\thread.cpp.i

CMakeFiles/cpuScheduller.dir/thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpuScheduller.dir/thread.cpp.s"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S Z:\CS\CSCI442\cpuScheduller\thread.cpp -o CMakeFiles\cpuScheduller.dir\thread.cpp.s

CMakeFiles/cpuScheduller.dir/burst.cpp.obj: CMakeFiles/cpuScheduller.dir/flags.make
CMakeFiles/cpuScheduller.dir/burst.cpp.obj: ../burst.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=Z:\CS\CSCI442\cpuScheduller\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/cpuScheduller.dir/burst.cpp.obj"
	C:\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpuScheduller.dir\burst.cpp.obj -c Z:\CS\CSCI442\cpuScheduller\burst.cpp

CMakeFiles/cpuScheduller.dir/burst.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpuScheduller.dir/burst.cpp.i"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E Z:\CS\CSCI442\cpuScheduller\burst.cpp > CMakeFiles\cpuScheduller.dir\burst.cpp.i

CMakeFiles/cpuScheduller.dir/burst.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpuScheduller.dir/burst.cpp.s"
	C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S Z:\CS\CSCI442\cpuScheduller\burst.cpp -o CMakeFiles\cpuScheduller.dir\burst.cpp.s

# Object files for target cpuScheduller
cpuScheduller_OBJECTS = \
"CMakeFiles/cpuScheduller.dir/main.cpp.obj" \
"CMakeFiles/cpuScheduller.dir/process.cpp.obj" \
"CMakeFiles/cpuScheduller.dir/event.cpp.obj" \
"CMakeFiles/cpuScheduller.dir/thread.cpp.obj" \
"CMakeFiles/cpuScheduller.dir/burst.cpp.obj"

# External object files for target cpuScheduller
cpuScheduller_EXTERNAL_OBJECTS =

cpuScheduller.exe: CMakeFiles/cpuScheduller.dir/main.cpp.obj
cpuScheduller.exe: CMakeFiles/cpuScheduller.dir/process.cpp.obj
cpuScheduller.exe: CMakeFiles/cpuScheduller.dir/event.cpp.obj
cpuScheduller.exe: CMakeFiles/cpuScheduller.dir/thread.cpp.obj
cpuScheduller.exe: CMakeFiles/cpuScheduller.dir/burst.cpp.obj
cpuScheduller.exe: CMakeFiles/cpuScheduller.dir/build.make
cpuScheduller.exe: CMakeFiles/cpuScheduller.dir/linklibs.rsp
cpuScheduller.exe: CMakeFiles/cpuScheduller.dir/objects1.rsp
cpuScheduller.exe: CMakeFiles/cpuScheduller.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=Z:\CS\CSCI442\cpuScheduller\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable cpuScheduller.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cpuScheduller.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpuScheduller.dir/build: cpuScheduller.exe

.PHONY : CMakeFiles/cpuScheduller.dir/build

CMakeFiles/cpuScheduller.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cpuScheduller.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cpuScheduller.dir/clean

CMakeFiles/cpuScheduller.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" Z:\CS\CSCI442\cpuScheduller Z:\CS\CSCI442\cpuScheduller Z:\CS\CSCI442\cpuScheduller\cmake-build-debug Z:\CS\CSCI442\cpuScheduller\cmake-build-debug Z:\CS\CSCI442\cpuScheduller\cmake-build-debug\CMakeFiles\cpuScheduller.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpuScheduller.dir/depend

