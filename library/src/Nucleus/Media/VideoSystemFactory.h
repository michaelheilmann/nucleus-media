// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/OOP/Include.h"

// Forward declaration.
typedef struct Nucleus_Media_VideoSystem Nucleus_Media_VideoSystem;

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.Media.VideoSystemFactory",
                             Nucleus_Media_VideoSystemFactory,
                             Nucleus_Object)
#define NUCLEUS_MEDIA_VIDEOSYSTEMFACTORY(p) ((Nucleus_Media_VideoSystemFactory *)(p))
#define NUCLEUS_MEDIA_VIDEOSYSTEMFACTORY_CLASS(p) ((Nucleus_Media_VideoSystemFactory_Class *)(p))

struct Nucleus_Media_VideoSystemFactory
{
    Nucleus_Object parent;
}; // struct Nucleus_Media_VideoSystemFactory

struct Nucleus_Media_VideoSystemFactory_Class
{
    Nucleus_Object_Class parent;
    Nucleus_Status (*createSystem)(Nucleus_Media_VideoSystemFactory *self, Nucleus_Media_VideoSystem **system);
    Nucleus_Status (*getSystemName)(Nucleus_Media_VideoSystemFactory *self, Nucleus_String **systemName);
	Nucleus_Status (*getConfigurations)(Nucleus_Media_VideoSystemFactory *self, Nucleus_ObjectArray **configurations);
}; // struct Nucleus_Media_VideoSystemFactory_Class

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemFactory_construct
    (
        Nucleus_Media_VideoSystemFactory *self
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemFactory_getSystemName
    (
        Nucleus_Media_VideoSystemFactory *self,
        Nucleus_String **systemName
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemFactory_createSystem
    (
        Nucleus_Media_VideoSystemFactory *self,
        Nucleus_Media_VideoSystem **system
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemFactory_getConfigurations
    (
        Nucleus_Media_VideoSystemFactory *self,
        Nucleus_ObjectArray **configurations
    );
