// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/VideoSystemWindow.h"

#define Nucleus_Media_Plugin_OpenGL_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_OpenGL_Export,
                             u8"Nucleus.Media.Plugin.OpenGL.VideoSystemWindow",
                             Nucleus_Media_Plugin_OpenGL_VideoSystemWindow,
                             Nucleus_Media_VideoSystemWindow)
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_VIDEOSYSTEMWINDOW(p) ((Nucleus_Media_Plugin_OpenGL_VideoSystem *)(p))
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_VIDEOSYSTEMWINDOW_CLASS(p) ((Nucleus_Media_Plugin_OpenGL_VideoSystem_Class *)(p))

struct Nucleus_Media_Plugin_OpenGL_VideoSystemWindow
{
    Nucleus_Media_VideoSystemWindow parent;
}; // struct Nucleus_Media_Plugin_OpenGL_VideoSystemWindow

struct Nucleus_Media_Plugin_OpenGL_VideoSystemWindow_Class
{
    Nucleus_Media_VideoSystemWindow_Class parent;
}; // struct Nucleus_Media_Plugin_OpenGL_VideoSystemWindow_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_VideoSystemWindow_construct
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemWindow *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_VideoSystemWindow_create
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemWindow **videoSystemWindow
    );
