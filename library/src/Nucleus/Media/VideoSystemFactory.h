// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/OOP/Include.h"

// Forward declaration.
typedef struct Nucleus_VideoSystem Nucleus_VideoSystem;

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.VideoSystemFactory",
                             Nucleus_VideoSystemFactory,
                             Nucleus_Object)
#define NUCLEUS_VIDEOSYSTEMFACTORY(p) ((Nucleus_VideoSystemFactory *)(p))
#define NUCLEUS_VIDEOSYSTEMFACTORY_CLASS(p) ((Nucleus_VideoSystemFactory_Class *)(p))

struct Nucleus_VideoSystemFactory_Class
{
    Nucleus_Object_Class parent;
    Nucleus_Status (*create)(Nucleus_VideoSystemFactory *self, Nucleus_VideoSystem **videoSystem);
    Nucleus_Status (*getName)(Nucleus_VideoSystemFactory *self, Nucleus_String **name);
}; // struct Nucleus_VideoSystemFactory_Class

struct Nucleus_VideoSystemFactory
{
    Nucleus_Object parent;
    Nucleus_String *name;
}; // struct Nucleus_VideoSystemFactory

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_VideoSystemFactory_construct
    (
        Nucleus_VideoSystemFactory *self
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_VideoSystemFactory_getName
    (
        Nucleus_VideoSystemFactory *self,
        Nucleus_String **name
    );
