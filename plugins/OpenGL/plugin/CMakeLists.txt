# Copyright (c) 2018 Michael Heilmann

# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)

# Define the plugin.
define_dynamic_library(Nucleus.Media Nucleus.Media.Plugin.OpenGL ${NUCLEUS_LANGUAGE_ID_C})
target_link_libraries(Nucleus.Media.Plugin.OpenGL PRIVATE Nucleus.Media.Library)

if (${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_CYGWIN} OR
    ${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_LINUX})
	# Link to (lib)GL.
    target_link_libraries(Nucleus.Media.Plugin.OpenGL PRIVATE GL)
    # Link to (lib)Xext and (lib)X11.
    target_link_libraries(Nucleus.Media.Plugin.OpenGL PRIVATE Xext X11)
endif()

if (${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_WINDOWS})
	# Link to OpenGL.
    target_link_libraries(Nucleus.Media.Plugin.OpenGL PRIVATE OpenGL32)
endif()
