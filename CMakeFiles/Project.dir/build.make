# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = "/home/matt/Desktop/Files/Programming Projects/Game"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/matt/Desktop/Files/Programming Projects/Game"

# Include any dependencies generated for this target.
include CMakeFiles/Project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project.dir/flags.make

CMakeFiles/Project.dir/animations.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/animations.o: animations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Project.dir/animations.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/animations.o -c "/home/matt/Desktop/Files/Programming Projects/Game/animations.cpp"

CMakeFiles/Project.dir/animations.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/animations.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/matt/Desktop/Files/Programming Projects/Game/animations.cpp" > CMakeFiles/Project.dir/animations.i

CMakeFiles/Project.dir/animations.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/animations.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/matt/Desktop/Files/Programming Projects/Game/animations.cpp" -o CMakeFiles/Project.dir/animations.s

CMakeFiles/Project.dir/camera.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/camera.o: camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Project.dir/camera.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/camera.o -c "/home/matt/Desktop/Files/Programming Projects/Game/camera.cpp"

CMakeFiles/Project.dir/camera.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/camera.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/matt/Desktop/Files/Programming Projects/Game/camera.cpp" > CMakeFiles/Project.dir/camera.i

CMakeFiles/Project.dir/camera.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/camera.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/matt/Desktop/Files/Programming Projects/Game/camera.cpp" -o CMakeFiles/Project.dir/camera.s

CMakeFiles/Project.dir/character.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/character.o: character.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Project.dir/character.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/character.o -c "/home/matt/Desktop/Files/Programming Projects/Game/character.cpp"

CMakeFiles/Project.dir/character.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/character.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/matt/Desktop/Files/Programming Projects/Game/character.cpp" > CMakeFiles/Project.dir/character.i

CMakeFiles/Project.dir/character.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/character.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/matt/Desktop/Files/Programming Projects/Game/character.cpp" -o CMakeFiles/Project.dir/character.s

CMakeFiles/Project.dir/enemy.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/enemy.o: enemy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Project.dir/enemy.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/enemy.o -c "/home/matt/Desktop/Files/Programming Projects/Game/enemy.cpp"

CMakeFiles/Project.dir/enemy.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/enemy.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/matt/Desktop/Files/Programming Projects/Game/enemy.cpp" > CMakeFiles/Project.dir/enemy.i

CMakeFiles/Project.dir/enemy.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/enemy.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/matt/Desktop/Files/Programming Projects/Game/enemy.cpp" -o CMakeFiles/Project.dir/enemy.s

CMakeFiles/Project.dir/gamestate.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/gamestate.o: gamestate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Project.dir/gamestate.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/gamestate.o -c "/home/matt/Desktop/Files/Programming Projects/Game/gamestate.cpp"

CMakeFiles/Project.dir/gamestate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/gamestate.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/matt/Desktop/Files/Programming Projects/Game/gamestate.cpp" > CMakeFiles/Project.dir/gamestate.i

CMakeFiles/Project.dir/gamestate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/gamestate.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/matt/Desktop/Files/Programming Projects/Game/gamestate.cpp" -o CMakeFiles/Project.dir/gamestate.s

CMakeFiles/Project.dir/gui.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/gui.o: gui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Project.dir/gui.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/gui.o -c "/home/matt/Desktop/Files/Programming Projects/Game/gui.cpp"

CMakeFiles/Project.dir/gui.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/gui.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/matt/Desktop/Files/Programming Projects/Game/gui.cpp" > CMakeFiles/Project.dir/gui.i

CMakeFiles/Project.dir/gui.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/gui.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/matt/Desktop/Files/Programming Projects/Game/gui.cpp" -o CMakeFiles/Project.dir/gui.s

CMakeFiles/Project.dir/inventory.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/inventory.o: inventory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Project.dir/inventory.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/inventory.o -c "/home/matt/Desktop/Files/Programming Projects/Game/inventory.cpp"

CMakeFiles/Project.dir/inventory.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/inventory.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/matt/Desktop/Files/Programming Projects/Game/inventory.cpp" > CMakeFiles/Project.dir/inventory.i

CMakeFiles/Project.dir/inventory.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/inventory.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/matt/Desktop/Files/Programming Projects/Game/inventory.cpp" -o CMakeFiles/Project.dir/inventory.s

CMakeFiles/Project.dir/main.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/main.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Project.dir/main.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/main.o -c "/home/matt/Desktop/Files/Programming Projects/Game/main.cpp"

CMakeFiles/Project.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/main.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/matt/Desktop/Files/Programming Projects/Game/main.cpp" > CMakeFiles/Project.dir/main.i

CMakeFiles/Project.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/main.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/matt/Desktop/Files/Programming Projects/Game/main.cpp" -o CMakeFiles/Project.dir/main.s

CMakeFiles/Project.dir/map.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/map.o: map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Project.dir/map.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/map.o -c "/home/matt/Desktop/Files/Programming Projects/Game/map.cpp"

CMakeFiles/Project.dir/map.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/map.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/matt/Desktop/Files/Programming Projects/Game/map.cpp" > CMakeFiles/Project.dir/map.i

CMakeFiles/Project.dir/map.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/map.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/matt/Desktop/Files/Programming Projects/Game/map.cpp" -o CMakeFiles/Project.dir/map.s

CMakeFiles/Project.dir/perlin.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/perlin.o: perlin.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Project.dir/perlin.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/perlin.o -c "/home/matt/Desktop/Files/Programming Projects/Game/perlin.cpp"

CMakeFiles/Project.dir/perlin.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/perlin.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/matt/Desktop/Files/Programming Projects/Game/perlin.cpp" > CMakeFiles/Project.dir/perlin.i

CMakeFiles/Project.dir/perlin.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/perlin.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/matt/Desktop/Files/Programming Projects/Game/perlin.cpp" -o CMakeFiles/Project.dir/perlin.s

CMakeFiles/Project.dir/projectile.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/projectile.o: projectile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Project.dir/projectile.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/projectile.o -c "/home/matt/Desktop/Files/Programming Projects/Game/projectile.cpp"

CMakeFiles/Project.dir/projectile.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/projectile.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/matt/Desktop/Files/Programming Projects/Game/projectile.cpp" > CMakeFiles/Project.dir/projectile.i

CMakeFiles/Project.dir/projectile.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/projectile.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/matt/Desktop/Files/Programming Projects/Game/projectile.cpp" -o CMakeFiles/Project.dir/projectile.s

CMakeFiles/Project.dir/utils.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/utils.o: utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Project.dir/utils.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/utils.o -c "/home/matt/Desktop/Files/Programming Projects/Game/utils.cpp"

CMakeFiles/Project.dir/utils.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/utils.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/matt/Desktop/Files/Programming Projects/Game/utils.cpp" > CMakeFiles/Project.dir/utils.i

CMakeFiles/Project.dir/utils.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/utils.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/matt/Desktop/Files/Programming Projects/Game/utils.cpp" -o CMakeFiles/Project.dir/utils.s

# Object files for target Project
Project_OBJECTS = \
"CMakeFiles/Project.dir/animations.o" \
"CMakeFiles/Project.dir/camera.o" \
"CMakeFiles/Project.dir/character.o" \
"CMakeFiles/Project.dir/enemy.o" \
"CMakeFiles/Project.dir/gamestate.o" \
"CMakeFiles/Project.dir/gui.o" \
"CMakeFiles/Project.dir/inventory.o" \
"CMakeFiles/Project.dir/main.o" \
"CMakeFiles/Project.dir/map.o" \
"CMakeFiles/Project.dir/perlin.o" \
"CMakeFiles/Project.dir/projectile.o" \
"CMakeFiles/Project.dir/utils.o"

# External object files for target Project
Project_EXTERNAL_OBJECTS =

Project: CMakeFiles/Project.dir/animations.o
Project: CMakeFiles/Project.dir/camera.o
Project: CMakeFiles/Project.dir/character.o
Project: CMakeFiles/Project.dir/enemy.o
Project: CMakeFiles/Project.dir/gamestate.o
Project: CMakeFiles/Project.dir/gui.o
Project: CMakeFiles/Project.dir/inventory.o
Project: CMakeFiles/Project.dir/main.o
Project: CMakeFiles/Project.dir/map.o
Project: CMakeFiles/Project.dir/perlin.o
Project: CMakeFiles/Project.dir/projectile.o
Project: CMakeFiles/Project.dir/utils.o
Project: CMakeFiles/Project.dir/build.make
Project: CMakeFiles/Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable Project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project.dir/build: Project

.PHONY : CMakeFiles/Project.dir/build

CMakeFiles/Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Project.dir/clean

CMakeFiles/Project.dir/depend:
	cd "/home/matt/Desktop/Files/Programming Projects/Game" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/matt/Desktop/Files/Programming Projects/Game" "/home/matt/Desktop/Files/Programming Projects/Game" "/home/matt/Desktop/Files/Programming Projects/Game" "/home/matt/Desktop/Files/Programming Projects/Game" "/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles/Project.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Project.dir/depend
