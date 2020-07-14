# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" "/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles/progress.marks"
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/home/matt/Desktop/Files/Programming Projects/Game/CMakeFiles" 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named a.out

# Build rule for target.
a.out: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 a.out
.PHONY : a.out

# fast build rule for target.
a.out/fast:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/build
.PHONY : a.out/fast

# target to build an object file
animations.o:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/animations.o
.PHONY : animations.o

# target to preprocess a source file
animations.i:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/animations.i
.PHONY : animations.i

# target to generate assembly for a file
animations.s:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/animations.s
.PHONY : animations.s

# target to build an object file
camera.o:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/camera.o
.PHONY : camera.o

# target to preprocess a source file
camera.i:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/camera.i
.PHONY : camera.i

# target to generate assembly for a file
camera.s:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/camera.s
.PHONY : camera.s

# target to build an object file
character.o:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/character.o
.PHONY : character.o

# target to preprocess a source file
character.i:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/character.i
.PHONY : character.i

# target to generate assembly for a file
character.s:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/character.s
.PHONY : character.s

# target to build an object file
enemy.o:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/enemy.o
.PHONY : enemy.o

# target to preprocess a source file
enemy.i:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/enemy.i
.PHONY : enemy.i

# target to generate assembly for a file
enemy.s:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/enemy.s
.PHONY : enemy.s

# target to build an object file
gamestate.o:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/gamestate.o
.PHONY : gamestate.o

# target to preprocess a source file
gamestate.i:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/gamestate.i
.PHONY : gamestate.i

# target to generate assembly for a file
gamestate.s:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/gamestate.s
.PHONY : gamestate.s

# target to build an object file
gui.o:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/gui.o
.PHONY : gui.o

# target to preprocess a source file
gui.i:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/gui.i
.PHONY : gui.i

# target to generate assembly for a file
gui.s:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/gui.s
.PHONY : gui.s

# target to build an object file
inventory.o:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/inventory.o
.PHONY : inventory.o

# target to preprocess a source file
inventory.i:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/inventory.i
.PHONY : inventory.i

# target to generate assembly for a file
inventory.s:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/inventory.s
.PHONY : inventory.s

# target to build an object file
main.o:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/main.o
.PHONY : main.o

# target to preprocess a source file
main.i:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/main.i
.PHONY : main.i

# target to generate assembly for a file
main.s:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/main.s
.PHONY : main.s

# target to build an object file
map.o:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/map.o
.PHONY : map.o

# target to preprocess a source file
map.i:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/map.i
.PHONY : map.i

# target to generate assembly for a file
map.s:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/map.s
.PHONY : map.s

# target to build an object file
perlin.o:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/perlin.o
.PHONY : perlin.o

# target to preprocess a source file
perlin.i:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/perlin.i
.PHONY : perlin.i

# target to generate assembly for a file
perlin.s:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/perlin.s
.PHONY : perlin.s

# target to build an object file
projectile.o:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/projectile.o
.PHONY : projectile.o

# target to preprocess a source file
projectile.i:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/projectile.i
.PHONY : projectile.i

# target to generate assembly for a file
projectile.s:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/projectile.s
.PHONY : projectile.s

# target to build an object file
utils.o:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/utils.o
.PHONY : utils.o

# target to preprocess a source file
utils.i:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/utils.i
.PHONY : utils.i

# target to generate assembly for a file
utils.s:
	$(MAKE) -f CMakeFiles/a.out.dir/build.make CMakeFiles/a.out.dir/utils.s
.PHONY : utils.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... a.out"
	@echo "... animations.o"
	@echo "... animations.i"
	@echo "... animations.s"
	@echo "... camera.o"
	@echo "... camera.i"
	@echo "... camera.s"
	@echo "... character.o"
	@echo "... character.i"
	@echo "... character.s"
	@echo "... enemy.o"
	@echo "... enemy.i"
	@echo "... enemy.s"
	@echo "... gamestate.o"
	@echo "... gamestate.i"
	@echo "... gamestate.s"
	@echo "... gui.o"
	@echo "... gui.i"
	@echo "... gui.s"
	@echo "... inventory.o"
	@echo "... inventory.i"
	@echo "... inventory.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... map.o"
	@echo "... map.i"
	@echo "... map.s"
	@echo "... perlin.o"
	@echo "... perlin.i"
	@echo "... perlin.s"
	@echo "... projectile.o"
	@echo "... projectile.i"
	@echo "... projectile.s"
	@echo "... utils.o"
	@echo "... utils.i"
	@echo "... utils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

