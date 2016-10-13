#pragma once

#include "Nucleus/Media/OOP/Include.h"

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.Media.Plugin",
                             Nucleus_Media_Plugin,
                             Nucleus_Object)
#define NUCLEUS_MEDIA_PLUGIN(p) ((Nucleus_Media_Plugin *)(p))
#define NUCLEUS_MEDIA_PLUGIN_CLASS(p) ((Nucleus_Media_Plugin_Class *)(p))

struct Nucleus_Media_Plugin_Class
{
    Nucleus_Object_Class parent;
    Nucleus_NonNull() Nucleus_Status (*getName)(Nucleus_Media_Plugin *, Nucleus_String **);
    Nucleus_NonNull() Nucleus_Status (*startup)(Nucleus_Media_Plugin *);
    Nucleus_AlwaysSucceed() Nucleus_NonNull() Nucleus_Status (*shutdown)(Nucleus_Media_Plugin *);
}; // struct Nucleus_Media_Plugin_Class

struct Nucleus_Media_Plugin
{
    Nucleus_Object parent;
}; // struct Nucleus_Media_Plugin

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_construct
    (
        Nucleus_Media_Plugin *self
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_getName
    (
        Nucleus_Media_Plugin *self,
        Nucleus_String **name
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_startup
    (
        Nucleus_Media_Plugin *self
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_shutdown
    (
        Nucleus_Media_Plugin *self
    );
