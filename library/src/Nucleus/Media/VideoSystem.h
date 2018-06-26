// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/OOP/Include.h"

// Forward declarations.
typedef struct Nucleus_Media_VideoSystemWindow Nucleus_Media_VideoSystemWindow;

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.Media.VideoSystem",
                             Nucleus_Media_VideoSystem,
                             Nucleus_Object)
#define NUCLEUS_MEDIA_VIDEOSYSTEM(p) ((Nucleus_Media_VideoSystem *)(p))
#define NUCLEUS_MEDIA_VIDEOSYSTEM_CLASS(p) ((Nucleus_Media_VideoSystem_Class *)(p))

struct Nucleus_Media_VideoSystem
{
    Nucleus_Object parent;
}; // struct Nucleus_Media_VideoSystem

struct Nucleus_Media_VideoSystem_Class
{
    Nucleus_Object_Class parent;
	Nucleus_NonNull() Nucleus_Status (*createWindow)(Nucleus_Media_VideoSystem *, Nucleus_Media_VideoSystemWindow **);
}; // struct Nucleus_Media_VideoSystem_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystem_construct
    (
        Nucleus_Media_VideoSystem *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystem_createWinow
	(
		Nucleus_Media_VideoSystem *self,
		Nucleus_Media_VideoSystemWindow **window
	);
