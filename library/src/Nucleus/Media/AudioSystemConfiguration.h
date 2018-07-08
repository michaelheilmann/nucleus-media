// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/OOP/Include.h"

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.Media.AudioSystemConfiguration",
                             Nucleus_Media_AudioSystemConfiguration,
                             Nucleus_Object)
#define NUCLEUS_MEDIA_AUDIOSYSTEMCONFIGURATION(p) ((Nucleus_Media_AudioSystemConfiguration *)(p))
#define NUCLEUS_MEDIA_AUDIOSYSTEMCONFIGURATION_CLASS(p) ((Nucleus_Media_AudioSystemConfiguration_Class *)(p))

struct Nucleus_Media_AudioSystemConfiguration_Class
{
    Nucleus_Object_Class parent;
	Nucleus_Status (*compare)(const Nucleus_Media_AudioSystemConfiguration *self,
	                          const Nucleus_Object *other);
}; // struct Nucleus_Media_AudioSystemConfiguration_Class

struct Nucleus_Media_AudioSystemConfiguration
{
    Nucleus_Object parent;
}; // struct Nucleus_Media_AudioSystemConfiguration

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_AudioSystemConfiguration_construct
    (
        Nucleus_Media_AudioSystemConfiguration *self
    );

Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_Media_AudioSystemConfiguration_create
    (
        Nucleus_Media_AudioSystemConfiguration **audioSystemConfiguration
    );
