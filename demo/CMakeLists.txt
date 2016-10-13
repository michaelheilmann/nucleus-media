# Copyright (c) 2018 Michael Heilmann
# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)
# Define the demo.
define_executable(Nucleus.Media Nucleus.Media.Demo ${NUCLEUS_LANGUAGE_ID_C})
target_link_libraries(Nucleus.Media.Demo PRIVATE Nucleus.Media.Library)
# Windows: Visibility of symbols.
if (${Nucleus.Media.Demo_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_WINDOWS})
  #target_compile_options(Nucleus.Media.Demo PRIVATE -DNucleus_Media_Library_Import)
endif()
