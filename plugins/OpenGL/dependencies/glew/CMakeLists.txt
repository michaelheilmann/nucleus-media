# Copyright (c) 2018 Michael Heilmann
# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)
# Define the static library.
define_static_library(Nucleus.Media Nucleus.Media.Glew ${NUCLEUS_LANGUAGE_ID_C})

# Requires OpenGL.
# This requires you to install X11 on Cygwin.
# TODO: Remove dependency to GLUT.
find_package(OpenGL REQUIRED)
target_link_libraries(Nucleus.Media.Glew PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

# glew include directory and library
target_compile_definitions(Nucleus.Media.Glew PUBLIC GLEW_STATIC)
