// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/VideoSystemFactory.h"

// Forward declaration.
typedef struct Nucleus_VideoSystem Nucleus_VideoSystem;

#define Nucleus_Media_Plugin_OpenGL_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_OpenGL_Export,
                             "Nucleus.Media.Plugin.OpenGL.VideoSystemFactory",
                             Nucleus_Media_Plugin_OpenGL_VideoSystemFactory,
                             Nucleus_Media_VideoSystemFactory)
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_VIDEOSYSTEMFACTORY(p) ((Nucleus_Media_Plugin_OpenGL_VideoSystemFactory *)(p))
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_VIDEOSYSTEMFACTORY_CLASS(p) ((Nucleus_Media_Plugin_OpenGL_VideoSystemFactory_Class *)(p))

struct Nucleus_Media_Plugin_OpenGL_VideoSystemFactory_Class
{
    Nucleus_VideoSystemFactory_Class parent;
}; // struct Nucleus_Media_Plugin_OpenGL_VideoSystemFactory_Class

struct Nucleus_Media_Plugin_OpenGL_VideoSystemFactory
{
    Nucleus_VideoSystemFactory parent;
    Nucleus_String *name;
}; // struct Nucleus_Media_Plugin_OpenGL_VideoSystemFactory

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_VideoSystemFactory_construct
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemFactory *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_VideoSystemFactory_create
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemFactory **videoSystemFactory
    );
