// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus.Media.Plugin.OpenGL/VideoSystem.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)

#include<stdio.h>
#include<X11/X.h>
#include<X11/Xlib.h>

// Forward declaration.
typedef struct Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow;

#define Nucleus_Media_Plugin_OpenGL_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_OpenGL_Export,
                             u8"Nucleus.Media.Plugin.OpenGL.GLX.VideoSystem",
                             Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem,
                             Nucleus_Media_Plugin_OpenGL_VideoSystem)
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_GLX_VIDEOSYSTEM(p) ((Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem *)(p))
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_GLX_VIDEOSYSTEM_CLASS(p) ((Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem_Class *)(p))

struct Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem
{
    Nucleus_Media_Plugin_OpenGL_VideoSystem parent;
    Display *display;
    Window desktopWindow;
}; // struct Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem

struct Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem_Class
{
    Nucleus_Media_Plugin_OpenGL_VideoSystem_Class parent;
}; // struct Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem_construct
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem_create
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem **videoSystem
    );

#endif
