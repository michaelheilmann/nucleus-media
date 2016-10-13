# Copyright (c) 2018 Michael Heilmann
# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)
# Define the plugin.
define_dynamic_library(Nucleus.Media Nucleus.Media.Plugin.Direct3D ${NUCLEUS_LANGUAGE_ID_C})
target_link_libraries(Nucleus.Media.Plugin.Direct3D Nucleus.Media.Library)
# Windows: Visibility of symbols.
if (${Nucleus.Media.Plugin.Direct3D_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_WINDOWS})
  #target_compile_options(Nucleus.Media.Plugin.Direct3D PRIVATE -DNucleus_Media_Library_Export)
endif()
