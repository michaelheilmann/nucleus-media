# Copyright (c) 2017, 2018 Michael Heilmann
# Assert minimum CMake version.
cmake_minimum_required (VERSION 3.8)

# Default to "static" (as opposed to "shared") variant.
if (Nucleus.Media-Shared)
  set(Nucleus.Media.Library-Shared ${Nucleus.Media-Shared})
else()
  set(Nucleus.Media.Library-Shared OFF)
endif()

# Define the library.
if (Nucleus.Media.Library-Shared)
  # Define the shared library.
  define_shared_library(Nucleus.Media Nucleus.Media.Library ${NUCLEUS_LANGUAGE_ID_C})
else()
  # Define the static library.
  define_static_library(Nucleus.Media Nucleus.Media.Library ${NUCLEUS_LANGUAGE_ID_C})
endif()

target_link_libraries(Nucleus.Media.Library PUBLIC Nucleus.Library)
target_link_libraries(Nucleus.Media.Library PUBLIC Nucleus.Object.Library)
# GCC or Clang: Link library with the platform's dynamically loadable library libraries.
if (${Nucleus.Media.Library_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_GCC} OR ${Nucleus.Media.Library_C_COMPILER_ID} EQUAL ${NUCLEUS_C_COMPILER_ID_CLANG})
  target_link_libraries(Nucleus.Media.Library PUBLIC dl)
endif()

include(GenerateExportHeader)
generate_export_header(
    Nucleus.Media.Library
    EXPORT_MACRO_NAME Nucleus_Media_Library_Export
    NO_EXPORT_MACRO_NAME Nucleus_Media_Library_NoExport
    DEPRECATED_MACRO_NAME Nucleus_Media_Library_Deprecated  
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/src/Nucleus/Media/Exports.h)
target_include_directories(Nucleus.Media.Library PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/src)
if (Nucleus.Media.Library-Shared)
  set_target_properties(Nucleus.Media.Library PROPERTIES
                        COMPILE_FLAGS -DNUCLEUS_MEDIA_LIBRARY_STATIC_DEFINE)
endif()
