# Copyright (c) 2018 Michael Heilmann

# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)

# Find OpenGL.
#find_package(OpenGL REQUIRED COMPONENTS OpenGL EGL GLX)

# Define the plugin.
define_dynamic_library(Nucleus.Media Nucleus.Media.Plugin.OpenGL ${NUCLEUS_LANGUAGE_ID_C})
target_link_libraries(Nucleus.Media.Plugin.OpenGL PRIVATE Nucleus.Media.Library)
target_link_libraries(Nucleus.Media.Plugin.OpenGL PRIVATE Nucleus.Media.Glew)

if (${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_CYGWIN})
	target_include_directories(Nucleus.Media.Plugin.OpenGL PRIVATE "/usr/include")
	target_link_libraries(Nucleus.Media.Plugin.OpenGL PRIVATE GL)
	target_link_libraries(Nucleus.Media.Plugin.OpenGL PRIVATE X11)
endif()
