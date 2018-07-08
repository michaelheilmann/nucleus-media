# Copyright (c) 2018 Michael Heilmann

# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)

if (${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_WINDOWS})
  add_subdirectory(XAudio2)
  add_subdirectory(Direct3D)
endif()

if (${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_LINUX}   OR
    ${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_CYGWIN}  OR
    ${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_WINDOWS})
  add_subdirectory(OpenGL)
endif()

if (${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_MACOS})
  add_subdirectory(Metal)
endif()

if (${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_LINUX} OR
    ${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_MACOS} OR
    ${Nucleus.Media_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_CYGWIN})
  add_subdirectory(OpenAL)
endif()
