// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/VideoSystem.h"

typedef struct Nucleus_Media_Plugin_Direct3D_VideoSystemWindow Nucleus_Media_Plugin_Direct3D_VideoSystemWindow;

#define Nucleus_Media_Plugin_Direct3D_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_Direct3D_Export,
                             u8"Nucleus.Media.Plugin.Direct3D.VideoSystem",
                             Nucleus_Media_Plugin_Direct3D_VideoSystem,
                             Nucleus_Media_VideoSystem)
#define NUCLEUS_MEDIA_PLUGIN_DIRECT3D_VIDEOSYSTEM(p) ((Nucleus_Media_Plugin_Direct3D_VideoSystem *)(p))
#define NUCLEUS_MEDIA_PLUGIN_DIRECT3D_VIDEOSYSTEM_CLASS(p) ((Nucleus_Media_Plugin_Direct3D_VideoSystem_Class *)(p))

struct Nucleus_Media_Plugin_Direct3D_VideoSystem
{
    Nucleus_Media_VideoSystem parent;
}; // struct Nucleus_Media_Plugin_Direct3D_VideoSystem

struct Nucleus_Media_Plugin_Direct3D_VideoSystem_Class
{
    Nucleus_Media_VideoSystem_Class parent;
}; // struct Nucleus_Media_Plugin_Direct3D_VideoSystem_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_Direct3D_VideoSystem_construct
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystem *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_Direct3D_VideoSystem_create
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystem **videoSystem
    );
