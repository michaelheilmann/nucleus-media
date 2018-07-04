// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/VideoSystem.h"

#define Nucleus_Media_Plugin_Metal_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_Metal_Export,
                             u8"Nucleus.Media.Plugin.Metal.VideoSystem",
                             Nucleus_Media_Plugin_Metal_VideoSystem,
                             Nucleus_Media_VideoSystem)
#define NUCLEUS_MEDIA_PLUGIN_METAL_VIDEOSYSTEM(p) ((Nucleus_Media_Plugin_Metal_VideoSystem *)(p))
#define NUCLEUS_MEDIA_PLUGIN_METAL_VIDEOSYSTEM_CLASS(p) ((Nucleus_Media_Plugin_Metal_VideoSystem_Class *)(p))

struct Nucleus_Media_Plugin_Metal_VideoSystem
{
    Nucleus_Media_VideoSystem parent;
}; // struct Nucleus_Media_Plugin_Metal_VideoSystem

struct Nucleus_Media_Plugin_Metal_VideoSystem_Class
{
    Nucleus_Media_VideoSystem_Class parent;
}; // struct Nucleus_Media_Plugin_Metal_VideoSystem_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_Metal_VideoSystem_construct
    (
        Nucleus_Media_Plugin_Metal_VideoSystem *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_Metal_VideoSystem_create
    (
        Nucleus_Media_Plugin_Metal_VideoSystem **videoSystem
    );
