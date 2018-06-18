# Copyright (c) 2018 Michael Heilmann

# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)

# Add the plugin.
add_subdirectory(plugin)

# Add the dependencies.
add_subdirectory(dependencies/glew)
