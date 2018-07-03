// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/OOP/Include.h"

// Forward declaration.
typedef struct Nucleus_Media_AudioSystem Nucleus_Media_AudioSystem;

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.Media.AudioSystemFactory",
                             Nucleus_Media_AudioSystemFactory,
                             Nucleus_Object)
#define NUCLEUS_MEDIA_AUDIOSYSTEMFACTORY(p) ((Nucleus_Media_AudioSystemFactory *)(p))
#define NUCLEUS_MEDIA_AUDIOSYSTEMFACTORY_CLASS(p) ((Nucleus_Media_AudioSystemFactory_Class *)(p))

struct Nucleus_Media_AudioSystemFactory
{
    Nucleus_Object parent;
}; // struct Nucleus_Media_AudioSystemFactory

struct Nucleus_Media_AudioSystemFactory_Class
{
    Nucleus_Object_Class parent;
    Nucleus_Status (*createSystem)(Nucleus_Media_AudioSystemFactory *self, Nucleus_Media_AudioSystem **system);
    Nucleus_Status (*getSystemName)(Nucleus_Media_AudioSystemFactory *self, Nucleus_String **systemName);
	Nucleus_Status (*getConfigurations)(Nucleus_Media_AudioSystemFactory *self, Nucleus_ObjectArray **configurations);
}; // struct Nucleus_Media_AudioSystemFactory_Class

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_AudioSystemFactory_construct
    (
        Nucleus_Media_AudioSystemFactory *self
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_AudioSystemFactory_getSystemName
    (
        Nucleus_Media_AudioSystemFactory *self,
        Nucleus_String **systemName
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_AudioSystemFactory_createSystem
    (
        Nucleus_Media_AudioSystemFactory *self,
        Nucleus_Media_AudioSystem **system
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_AudioSystemFactory_getConfigurations
    (
        Nucleus_Media_AudioSystemFactory *self,
        Nucleus_ObjectArray **configurations
    );
