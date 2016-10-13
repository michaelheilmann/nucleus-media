# Copyright (c) 2018 Michael Heilmann
# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)
# Find OpenGL.
find_package(OpenGL REQUIRED)
# Define the plugin.
define_dynamic_library(Nucleus.Media Nucleus.Media.Plugin.OpenGL ${NUCLEUS_LANGUAGE_ID_C})
target_link_libraries(Nucleus.Media.Plugin.OpenGL PRIVATE Nucleus.Media.Library)
target_link_libraries(Nucleus.Media.Plugin.OpenGL PRIVATE Nucleus.Media.Glew)
# Windows: Visibility of symbols.
if (${Nucleus.Media.Plugin.OpenGL_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_WINDOWS})
  #target_compile_options(Nucleus.Media.Plugin.OpenGL PRIVATE -DNucleus_Media_Library_Export)
endif()
