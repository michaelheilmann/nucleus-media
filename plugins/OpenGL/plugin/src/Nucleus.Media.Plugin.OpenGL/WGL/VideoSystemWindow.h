// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus.Media.Plugin.OpenGL/VideoSystemWindow.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

typedef struct Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem;

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdio.h>

#define Nucleus_Media_Plugin_OpenGL_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_OpenGL_Export,
                             u8"Nucleus.Media.Plugin.OpenGL.WGL.VideoSystemWindow",
                             Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow,
                             Nucleus_Media_Plugin_OpenGL_VideoSystemWindow)
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_WGL_VIDEOSYSTEMWINDOW(p) ((Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow *)(p))
#define NUCLEUS_MEDIA_PLUGIN_OPENGL_WGL_VIDEOSYSTEMWINDOW_CLASS(p) ((Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow_Class *)(p))

struct Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow
{
    Nucleus_Media_Plugin_OpenGL_VideoSystemWindow parent;
    Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem *videoSystem;
    HWND hWnd;
    ATOM wndclass;
    HINSTANCE hInstance;
}; // struct Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow

struct Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow_Class
{
    Nucleus_Media_Plugin_OpenGL_VideoSystemWindow_Class parent;
}; // struct Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow_construct
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow *self,
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem *videoSystem
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow_create
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow **videoSystemWindow,
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem *videoSystem
    );

#endif
