# Copyright (c) 2017, 2018 Michael Heilmann

# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)

# The path to "Nucleus".
if (NOT NUCLEUS_PATH)
  set(NUCLEUS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nucleus)
endif()

# The path to "Nucleus: Object".
if (NOT NUCLEUS_OBJECT_PATH)
  set(NUCLEUS_OBJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nucleus-object)
endif()

# Include the "Nucleus" build system.
if (NUCLEUS_PATH)
  include(${NUCLEUS_PATH}/buildsystem/buildsystem.cmake)
endif()

# Define module.
define_module(Nucleus.Media)
detect_operating_system(Nucleus.Media)

# If "shared" is not defined, default to "ON".
if (NOT DEFINED Nucleus.Media-Shared)
  set(Nucleus.Media-Shared ON)
endif()

# Include "Nucleus" unless it is already included.
if (NOT NUCLEUS_INCLUDED)
  set(Nucleus-Shared ${Nucleus.Media-Shared})
  set(Nucleus-With-Optimizations ${Nucleus.Media-With-Optimizations})
  set(Nucleus-With-Debug-Information ${Nucleus.Media-With-Debug-Information})
  add_subdirectory(${NUCLEUS_PATH})
  set(NUCLEUS_INCLUDED YES)
endif()

# Include "Nucleus: Object" unless it is already included.
if (NOT NUCLEUS_OBJECT_INCLUDED)
  set(Nucleus.Object-Shared ${Nucleus.Media-Shared})
  set(Nucleus.Object-With-Optimizations ${Nucleus.Media-With-Optimizations})
  set(Nucleus.Object-With-Debug-Information ${Nucleus.Media-With-Debug-Information})
  add_subdirectory(${NUCLEUS_OBJECT_PATH})
  set(NUCLEUS_OBJECT_INCLUDED YES)
endif()

# Add module "library".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/library")

# Add module "demo".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/demo")

# Add module "plugins".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/plugins")

# Add module "test".
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
