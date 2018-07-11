// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Size.h"
#include "Nucleus/Media/Exports.h"
#include "Nucleus/Media/OOP/Include.h"
#include "Nucleus/Collections/PointerHashMap.h"

// Forward declarations.
typedef struct Nucleus_Media_AudioSystem Nucleus_Media_AudioSystem;
typedef struct Nucleus_Media_AudioSystemFactory Nucleus_Media_AudioSystemFactory;
typedef struct Nucleus_Media_AudioSystemConfiguration Nucleus_Media_AudioSystemConfiguration;
// Forward declarations.
typedef struct Nucleus_Media_VideoSystem Nucleus_Media_VideoSystem;
typedef struct Nucleus_Media_VideoSystemFactory Nucleus_Media_VideoSystemFactory;
typedef struct Nucleus_Media_VideoSystemConfiguration Nucleus_Media_VideoSystemConfiguration;

// `Nucleus_Media_Context` is a representation of a heavy-weight collection of resources pertaining
// to audio, video, and haptic functionality.
Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             u8"Nucleus.Media.Context",
                             Nucleus_Media_Context,
                             Nucleus_Object)
#define NUCLEUS_MEDIA_CONTEXT(p) ((Nucleus_Media_Context *)(p))
#define NUCLEUS_MEDIA_CONTEXT_CLASS(p) ((Nucleus_Media_Context_Class *)(p))

struct Nucleus_Media_Context
{
    Nucleus_Object parent;
    // Map of plugin names to plugins.
    Nucleus_Collections_PointerHashMap plugins;
    // List of video system factories.
    Nucleus_ObjectArray *videoSystemFactories;
    // List of audio system factories.
    Nucleus_ObjectArray *audioSystemFactories;
    // null or selected video system.
    Nucleus_Media_VideoSystem *videoSystem;
    // null or selected audio system.
    Nucleus_Media_AudioSystem *audioSystem;
}; // struct Nucleus_Media_Context

struct Nucleus_Media_Context_Class
{
    Nucleus_Object_Class parent;
}; // struct Nucleus_Media_Context_Class

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_construct
    (
        Nucleus_Media_Context *self
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_create
    (
        Nucleus_Media_Context **context
    );

// # `Nucleus_Media_Context_get`
// *Get the `Nucleus_Media_Context` singleton.*
// ## C Signature
// ```
// Nucleus_Status
// Nucleus_Media_Context_get
//   (
//       Nucleus_Media_Context **context
//   )
// ```
// ## Parameters
// - `context` a pointer to a `(Nucleus_Media_Context *)` variable
// ## Description
// If this function succeeds `*context` is assigned the address of a `Nucleus_Media_Context` object.
// This function fails iff `context` is a null pointer or the `Nucleus_Media_Context` singleton
// does not exist. `Nucleus_Status_InvalidArgument` is returned in the former case and
// `Nucleus_Status_NotExists` is returned in the latter case.
Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_get
    (
        Nucleus_Media_Context **context
    );

// # `Nucleus_Media_Context_startup`
// *Startup the `Nucleus_MediaContext` singleton.*
// ## C Signature
// ```
// Nucleus_Status
// Nucleus_Media_Context_startup
//     (
//     );
// ```
// ## Description
// If the `Nucleus_Media_Context` singleton does exist, `Nucleus_Status_Exists` is returned.
// If it does not exist, then it is created.
// If the creation fails, a non-zero status code is returned.
Nucleus_Media_Library_Export Nucleus_Status
Nucleus_Media_Context_initialize
    (
    );
 
// # `Nucleus_Media_Context_shutdown`
// *Shutdown the `Nucleus_Media_Context` singleton.*
// ## C Signature
// ```
// Nucleus_Status
// Nucleus_Media_Context_uninitialize
//     (
//     );
// ```
// ## Description
// If the `Nucleus_Media_Context` singleton does not exist, `Nucleus_Status_NotExists` is returned.
// If it does exist, it is destroyed.
Nucleus_Media_Library_Export Nucleus_Status
Nucleus_Media_Context_uninitialize
    (
    );

// Register an audio system factory.
// If an equivalent factory is already registered, #Nucleus_Status_AlreadyExists is returned.
Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_registerAudioSystemFactory
    (
        Nucleus_Media_Context *context,
        Nucleus_Media_AudioSystemFactory *audioSystemFactory
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_getAudioSystemFactories
    (
        Nucleus_Media_Context *context,
        Nucleus_ObjectEnumerator **enumerator
    );

// Register a video system factory.
// If an equivalent factory is already registered, #Nucleus_Status_AlreadyExists is returned.
Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_registerVideoSystemFactory
    (
        Nucleus_Media_Context *context,
        Nucleus_Media_VideoSystemFactory *videoSystemFactory
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_getVideoSystemFactories
    (
        Nucleus_Media_Context *context,
        Nucleus_ObjectEnumerator **enumerator  
    );

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Media_Context_startup
    (
        Nucleus_Media_Context *context,
        Nucleus_Status(*selectVideoSystemFactory)(Nucleus_Media_VideoSystemFactory **factory),
        Nucleus_Status(*selectVideoSystemConfiguration)(Nucleus_ObjectEnumerator *enumerator,
                                                        Nucleus_Media_VideoSystemConfiguration **configuration),
        Nucleus_Status(*selectAudioSystemFactory)(Nucleus_Media_AudioSystemFactory **factory),
        Nucleus_Status(*selectAudioSystemConfiguration)(Nucleus_ObjectEnumerator *enumerator,
                                                        Nucleus_Media_AudioSystemConfiguration **configuration)
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_shutdown
    (
        Nucleus_Media_Context *context
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_getVideoSystem
    (
        Nucleus_Media_Context *context,
        Nucleus_Media_VideoSystem **videoSystem
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_getAudioSystem
    (
        Nucleus_Media_Context *context,
        Nucleus_Media_AudioSystem **audioSystem
    );
