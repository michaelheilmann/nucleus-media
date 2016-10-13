# Copyright (c) 2017, 2018 Michael Heilmann
# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)
# Define the test.
define_test(Nucleus.Media Nucleus.Media.Test.Event ${NUCLEUS_LANGUAGE_ID_C})
target_link_libraries(Nucleus.Media.Test.Event PRIVATE Nucleus.Media.Library)
# Windows: Visibility of symbols.
if (${Nucleus.Media.Test.Event_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_WINDOWS})
  target_compile_options(Nucleus.Media.Test.Event PRIVATE -DNucleus_Media_Library_Import)
endif()
