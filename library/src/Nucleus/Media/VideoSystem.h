// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/OOP/Include.h"

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.Media.VideoSystem",
                             Nucleus_Media_VideoSystem,
                             Nucleus_Object)
#define NUCLEUS_MEDIA_VIDEOSYSTEM(p) ((Nucleus_Media_VideoSystem *)(p))
#define NUCLEUS_MEDIA_VIDEOSYSTEM_CLASS(p) ((Nucleus_Media_VideoSystem_Class *)(p))

struct Nucleus_Media_VideoSystem_Class
{
    Nucleus_Object_Class parent;
}; // struct Nucleus_Media_VideoSystem_Class

struct Nucleus_Media_VideoSystem
{
    Nucleus_Object parent;
}; // struct Nucleus_Media_VideoSystem

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystem_construct
    (
        Nucleus_Media_VideoSystem *self
    );
