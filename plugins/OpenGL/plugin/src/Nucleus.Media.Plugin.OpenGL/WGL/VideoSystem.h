// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus.Media.Plugin.OpenGL/VideoSystem.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

// Forward declaration.
typedef struct Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow;

#define Nucleus_Media_Plugin_OpenGL_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_OpenGL_Export,
                             u8"Nucleus.Media.Plugin.OpenGL.WGL.VideoSystem",
                             Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem,
                             Nucleus_Media_Plugin_OpenGL_VideoSystem)
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_WGL_VIDEOSYSTEM(p) ((Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem *)(p))
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_WGL_VIDEOSYSTEM_CLASS(p) ((Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem_Class *)(p))

struct Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem
{
    Nucleus_Media_Plugin_OpenGL_VideoSystem parent;
    Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow *window;
}; // struct Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem

struct Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem_Class
{
    Nucleus_Media_Plugin_OpenGL_VideoSystem_Class parent;
}; // struct Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem_construct
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem_create
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem **videoSystem
    );

#endif
