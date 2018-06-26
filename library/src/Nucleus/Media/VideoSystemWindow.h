// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/OOP/Include.h"

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.Media.VideoSystemWindow",
                             Nucleus_Media_VideoSystemWindow,
                             Nucleus_Object)
#define NUCLEUS_MEDIA_VIDEOSYSTEMWINDOW(p) ((Nucleus_Media_VideoSystemWindow *)(p))
#define NUCLEUS_MEDIA_VIDEOSYSTEMWINDOW_CLASS(p) ((Nucleus_Media_VideoSystemWindow_Class *)(p))

struct Nucleus_Media_VideoSystemWindow_Class
{
    Nucleus_Object_Class parent;
}; // struct Nucleus_Media_VideoSystemWindow_Class

struct Nucleus_Media_VideoSystemWindow
{
    Nucleus_Object parent;
}; // struct Nucleus_Media_VideoSystemWindow

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemWindow_construct
    (
        Nucleus_Media_VideoSystemWindow *self
    );