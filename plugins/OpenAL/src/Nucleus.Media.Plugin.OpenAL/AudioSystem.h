// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/AudioSystem.h"

#define Nucleus_Media_Plugin_OpenAL_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_OpenAL_Export,
                             u8"Nucleus.Media.Plugin.OpenAL.AudioSystem",
                             Nucleus_Media_Plugin_OpenAL_AudioSystem,
                             Nucleus_Media_AudioSystem)
#define NUCLEUS_MEDIA_PLUGIN_OPENAL_AUDIOSYSTEM(p) ((Nucleus_Media_Plugin_OpenAL_AudioSystem *)(p))
#define NUCLEUS_MEDIA_PLUGIN_OPENAL_AUDIOSYSTEM_CLASS(p) ((Nucleus_Media_Plugin_OpenAL_AudioSystem_Class *)(p))

struct Nucleus_Media_Plugin_OpenAL_AudioSystem
{
    Nucleus_Media_AudioSystem parent;
    Nucleus_String *systemName;
}; // struct Nucleus_Media_Plugin_OpenAL_AudioSystem

struct Nucleus_Media_Plugin_OpenAL_AudioSystem_Class
{
    Nucleus_Media_AudioSystem_Class parent;
}; // struct Nucleus_Media_Plugin_OpenAL_AudioSystem_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenAL_AudioSystem_construct
    (
        Nucleus_Media_Plugin_OpenAL_AudioSystem *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenAL_AudioSystem_create
    (
        Nucleus_Media_Plugin_OpenAL_AudioSystem **audioSystem
    );
