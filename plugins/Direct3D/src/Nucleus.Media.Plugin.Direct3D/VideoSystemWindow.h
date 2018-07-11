// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/VideoSystemWindow.h"

typedef struct Nucleus_Media_Plugin_Direct3D_VideoSystem Nucleus_Media_Plugin_Direct3D_VideoSystem;

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d12.h>

#include <stdio.h>

#define Nucleus_Media_Plugin_Direct3D_Export
Nucleus_ClassTypeDeclaration(Nucleus_Media_Plugin_Direct3D_Export,
                             u8"Nucleus.Media.Plugin.Direct3D.VideoSystemWindow",
                             Nucleus_Media_Plugin_Direct3D_VideoSystemWindow,
                             Nucleus_Media_VideoSystemWindow)
#define NUCLEUS_MEDIA_PLUGIN_DIRECT3D_VIDEOSYSTEMWINDOW(p) ((Nucleus_Media_Plugin_Direct3D_VideoSystemWindow *)(p))
#define NUCLEUS_MEDIA_PLUGIN_DIRECT3D_VIDEOSYSTEMWINDOW_CLASS(p) ((Nucleus_Media_Plugin_Direct3D_VideoSystemWindow_Class *)(p))

struct Nucleus_Media_Plugin_Direct3D_VideoSystemWindow
{
    Nucleus_Media_VideoSystemWindow parent;
    Nucleus_Media_Plugin_Direct3D_VideoSystem *videoSystem;
    HWND hWnd;
    ATOM wndclass;
    HINSTANCE hInstance;
    //
    ID3D12Device* device;
}; // struct Nucleus_Media_Plugin_Direct3D_VideoSystemWindow

struct Nucleus_Media_Plugin_Direct3D_VideoSystemWindow_Class
{
    Nucleus_Media_VideoSystemWindow_Class parent;
}; // struct Nucleus_Media_Plugin_Direct3D_VideoSystemWindow_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_Direct3D_VideoSystemWindow_construct
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemWindow *self,
        Nucleus_Media_Plugin_Direct3D_VideoSystem *videoSystem
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_Direct3D_VideoSystemWindow_create
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemWindow **videoSystemWindow,
        Nucleus_Media_Plugin_Direct3D_VideoSystem *videoSystem
    );
