// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/VideoSystem.h"
#include "Nucleus/Collections/PointerArray.h"

// Forward declaration.
typedef struct Nucleus_Media_Plugin_OpenGL_VideoSystemWindow Nucleus_Media_Plugin_OpenGL_VideoSystemWindow;

#define Nucleus_Media_Plugin_OpenGL_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_OpenGL_Export,
                             u8"Nucleus.Media.Plugin.OpenGL.VideoSystem",
                             Nucleus_Media_Plugin_OpenGL_VideoSystem,
                             Nucleus_Media_VideoSystem)
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_VIDEOSYSTEM(p) ((Nucleus_Media_Plugin_OpenGL_VideoSystem *)(p))
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_VIDEOSYSTEM_CLASS(p) ((Nucleus_Media_Plugin_OpenGL_VideoSystem_Class *)(p))

struct Nucleus_Media_Plugin_OpenGL_VideoSystem
{
    Nucleus_Media_VideoSystem parent;
    Nucleus_Media_Plugin_OpenGL_VideoSystemWindow *mainWindow; /* The main window. */
    Nucleus_Collections_PointerArray windows; /* List of windows. */
}; // struct Nucleus_Media_Plugin_OpenGL_VideoSystem

struct Nucleus_Media_Plugin_OpenGL_VideoSystem_Class
{
    Nucleus_Media_VideoSystem_Class parent;
}; // struct Nucleus_Media_Plugin_OpenGL_VideoSystem_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_VideoSystem_construct
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystem *self
    );
