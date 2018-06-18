// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/Plugin.h"

#define Nucleus_Media_Plugin_OpenAL_Export

Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_OpenAL_Export,
                             "Nucleus.Media.Plugin.OpenAL.Plugin",
                             Nucleus_Media_Plugin_OpenAL_Plugin,
                             Nucleus_Media_Plugin)
#define NUCLEUS_MEDIA_PLUGIN_XAUDIO2_PLUGIN(p) ((Nucleus_Media_Plugin_OpenAL_Plugin *)(p))
#define NUCLEUS_MEDIA_PLUGIN_XAUDIO2_PLUGIN_CLASS(p) ((Nucleus_Media_Plugin_OpenAL_Plugin_Class *)(p))

struct Nucleus_Media_Plugin_OpenAL_Plugin
{
    Nucleus_Media_Plugin parent;
    Nucleus_String *name;
}; // struct Nucleus_Media_Plugin_OpenAL_Plugin

struct Nucleus_Media_Plugin_OpenAL_Plugin_Class
{
    Nucleus_Media_Plugin_Class parent;
}; // struct Nucleus_Media_Plugin_OpenAL_Plugin_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenAL_Plugin_construct
    (
        Nucleus_Media_Plugin_OpenAL_Plugin *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenAL_Plugin_create
    (
        Nucleus_Media_Plugin_OpenAL_Plugin **plugin
    );
