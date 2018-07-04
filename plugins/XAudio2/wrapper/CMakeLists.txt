# Copyright (c) 2018 Michael Heilmann

# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)

# Define the plugin.
define_static_library(Nucleus.Media Nucleus.Media.XAudio2Wrapper.Library ${NUCLEUS_LANGUAGE_ID_CPP})
target_link_libraries(Nucleus.Media.XAudio2Wrapper.Library Nucleus.Library)
target_link_libraries(Nucleus.Media.XAudio2Wrapper.Library Xaudio2.lib)
