// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/Plugin.h"

#define Nucleus_Media_Plugin_Direct3D_Export

Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_Direct3D_Export,
                             u8"Nucleus.Media.Plugin.Direct3D.Plugin",
                             Nucleus_Media_Plugin_Direct3D_Plugin,
                             Nucleus_Media_Plugin)
#define NUCLEUS_MEDIA_PLUGIN_DIRECT3D_PLUGIN(p) ((Nucleus_Media_Plugin_Direct3D_Plugin *)(p))
#define NUCLEUS_MEDIA_PLUGIN_DIRECT3D_PLUGIN_CLASS(p) ((Nucleus_Media_Plugin_Direct3D_Plugin_Class *)(p))

struct Nucleus_Media_Plugin_Direct3D_Plugin
{
    Nucleus_Media_Plugin parent;
    Nucleus_String *name;
}; // struct Nucleus_Media_Plugin_Direct3D_Plugin

struct Nucleus_Media_Plugin_Direct3D_Plugin_Class
{
    Nucleus_Media_Plugin_Class parent;
}; // struct Nucleus_Media_Plugin_Direct3D_Plugin_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_Direct3D_Plugin_construct
    (
        Nucleus_Media_Plugin_Direct3D_Plugin *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_Direct3D_Plugin_create
    (
        Nucleus_Media_Plugin_Direct3D_Plugin **plugin
    );
