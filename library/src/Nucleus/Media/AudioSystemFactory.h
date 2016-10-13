// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/OOP/Include.h"

// Forward declaration.
typedef struct Nucleus_AudioSystem Nucleus_AudioSystem;

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.AudioSystemFactory",
                             Nucleus_AudioSystemFactory,
                             Nucleus_Object)
#define NUCLEUS_AUDIOSYSTEMFACTORY(p) ((Nucleus_AudioSystemFactory *)(p))
#define NUCLEUS_AUDIOSYSTEMFACTORY_CLASS(p) ((Nucleus_AudioSystemFactory_Class *)(p))

struct Nucleus_AudioSystemFactory_Class
{
    Nucleus_Object_Class parent;
    Nucleus_Status (*create)(Nucleus_AudioSystemFactory *self, Nucleus_AudioSystem **audioSystem);
    Nucleus_Status (*getName)(Nucleus_AudioSystemFactory *self, Nucleus_String **name);
}; // struct Nucleus_AudioSystemFactory_Class

struct Nucleus_AudioSystemFactory
{
    Nucleus_Object parent;
}; // struct Nucleus_AudioSystemFactory

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_AudioSystemFactory_construct
    (
        Nucleus_AudioSystemFactory *self
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_AudioSystemFactory_getName
    (
        Nucleus_AudioSystemFactory *self,
        Nucleus_String **name
    );
