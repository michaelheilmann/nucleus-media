// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/AudioSystemFactory.h"

// Forward declaration.
typedef struct Nucleus_Media_AudioSystem Nucleus_Media_AudioSystem;

#define Nucleus_Media_Plugin_XAudio2_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_XAudio2_Export,
                             "Nucleus.Media.Plugin.XAudio2.AudioSystemFactory",
                             Nucleus_Media_Plugin_XAudio2_AudioSystemFactory,
                             Nucleus_Media_AudioSystemFactory)
#define NUCLEUS_MEDIA_PLUGIN_XAUDIO2_AUDIOSYSTEMFACTORY(p) ((Nucleus_Media_Plugin_XAudio2_AudioSystemFactory *)(p))
#define NUCLEUS_MEDIA_PLUGIN_XAUDIO2_AUDIOSYSTEMFACTORY_CLASS(p) ((Nucleus_Media_Plugin_XAudio2_AudioSystemFactory_Class *)(p))

struct Nucleus_Media_Plugin_XAudio2_AudioSystemFactory
{
    Nucleus_Media_AudioSystemFactory parent;
    Nucleus_String *systemName;
}; // struct Nucleus_Media_Plugin_XAudio2_AudioSystemFactory

struct Nucleus_Media_Plugin_XAudio2_AudioSystemFactory_Class
{
    Nucleus_Media_AudioSystemFactory_Class parent;
}; // struct Nucleus_Media_Plugin_XAudio2_AudioSystemFactory_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_XAudio2_AudioSystemFactory_construct
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystemFactory *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_XAudio2_AudioSystemFactory_create
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystemFactory **AudioSystemFactory
    );
