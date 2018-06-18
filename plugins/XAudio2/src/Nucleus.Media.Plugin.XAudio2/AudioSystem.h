// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/AudioSystem.h"

#define Nucleus_Media_Plugin_XAudio2_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_XAudio2_Export,
                             u8"Nucleus.Media.Plugin.XAudio2.AudioSystem",
                             Nucleus_Media_Plugin_XAudio2_AudioSystem,
                             Nucleus_Media_AudioSystem)
#define NUCLEUS_MEDIA_PLUGIN_XAUDIO2_AUDIOSYSTEM(p) ((Nucleus_Media_Plugin_XAudio2_AudioSystem *)(p))
#define NUCLEUS_MEDIA_PLUGIN_XAUDIO2_AUDIOSYSTEM_CLASS(p) ((Nucleus_Media_Plugin_XAudio2_AudioSystem_Class *)(p))

struct Nucleus_Media_Plugin_XAudio2_AudioSystem
{
    Nucleus_Media_AudioSystem parent;
    Nucleus_String *systemName;
}; // struct Nucleus_Media_Plugin_XAudio2_AudioSystem

struct Nucleus_Media_Plugin_XAudio2_AudioSystem_Class
{
    Nucleus_Media_AudioSystem_Class parent;
}; // struct Nucleus_Media_Plugin_XAudio2_AudioSystem_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_XAudio2_AudioSystem_construct
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystem *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_XAudio2_AudioSystem_create
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystem **audioSystem
    );
