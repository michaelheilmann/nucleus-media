# Copyright (c) 2018 Michael Heilmann

# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)

# Define the plugin.
define_dynamic_library(Nucleus.Media Nucleus.Media.Plugin.Direct3D ${NUCLEUS_LANGUAGE_ID_C})
target_link_libraries(Nucleus.Media.Plugin.Direct3D Nucleus.Media.Library)
