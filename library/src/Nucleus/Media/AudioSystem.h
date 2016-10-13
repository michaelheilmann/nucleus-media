// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/OOP/Include.h"

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.Media.AudioSystem",
                             Nucleus_Media_AudioSystem,
                             Nucleus_Object)
#define NUCLEUS_MEDIA_AUDIOSYSTEM(p) ((Nucleus_Media_AudioSystem *)(p))
#define NUCLEUS_MEDIA_AUDIOSYSTEM_CLASS(p) ((Nucleus_Media_AudioSystem_Class *)(p))

struct Nucleus_Media_AudioSystem_Class
{
    Nucleus_Object_Class parent;
}; // struct Nucleus_Media_AudioSystem_Class

struct Nucleus_Media_AudioSystem
{
    Nucleus_Object parent;
}; // struct Nucleus_Media_AudioSystem

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_AudioSystem_construct
    (
        Nucleus_Media_AudioSystem *self
    );
