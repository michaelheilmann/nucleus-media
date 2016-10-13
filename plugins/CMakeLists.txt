# Copyright (c) 2018 Michael Heilmann
# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)
if (${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_WINDOWS})
  add_subdirectory(Direct3D)
endif()
add_subdirectory(OpenGL)
