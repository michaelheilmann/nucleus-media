# Copyright (c) 2018 Michael Heilmann

# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)

# Find OpenGL.
find_package(OpenGL REQUIRED)

# Define the plugin.
define_dynamic_library(Nucleus.Media Nucleus.Media.Plugin.OpenGL ${NUCLEUS_LANGUAGE_ID_C})
target_link_libraries(Nucleus.Media.Plugin.OpenGL PRIVATE Nucleus.Media.Library)
target_link_libraries(Nucleus.Media.Plugin.OpenGL PRIVATE Nucleus.Media.Glew)
