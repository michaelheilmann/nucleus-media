// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus.Media.Plugin.OpenGL/VideoSystemWindow.h"

typedef struct Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem;

#define Nucleus_Media_Plugin_OpenGL_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_OpenGL_Export,
                             u8"Nucleus.Media.Plugin.OpenGL.GLX.VideoSystemWindow",
                             Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow,
                             Nucleus_Media_Plugin_OpenGL_VideoSystemWindow)
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_GLX_VIDEOSYSTEMWINDOW(p) ((Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow *)(p))
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_GLX_VIDEOSYSTEMWINDOW_CLASS(p) ((Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow_Class *)(p))

struct Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow
{
    Nucleus_Media_Plugin_OpenGL_VideoSystemWindow parent;
    Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem *videoSystem;
}; // struct Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow

struct Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow_Class
{
    Nucleus_Media_Plugin_OpenGL_VideoSystemWindow_Class parent;
}; // struct Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow_construct
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow *self,
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem *videoSystem
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow_create
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow **videoSystemWindow,
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem *videoSystem
    );
