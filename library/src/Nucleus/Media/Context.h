// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Size.h"
#include "Nucleus/Media/Exports.h"
#include "Nucleus/Media//OOP/Include.h"

// Forward declarations.
typedef struct Nucleus_Media_AudioSystemFactory Nucleus_Media_AudioSystemFactory;
typedef struct Nucleus_Media_AudioSystemConfiguration Nucleus_Media_AudioSystemConfiguration;
typedef struct Nucleus_Media_VideoSystemFactory Nucleus_Media_VideoSystemFactory;
typedef struct Nucleus_Media_VideoSystemConfiguration Nucleus_Media_VideoSystemConfiguration;

// `Nucleus_MediaContext` is a representation of a heavy-weight collection of resources pertaining
// to audio, video, and haptic functionality.
typedef struct Nucleus_MediaContext Nucleus_MediaContext;
typedef struct Nucleus_Type Nucleus_Type;

// # `Nucleus_getMediaContext`
// *Get the `Nucleus_MediaContext` singleton.*
// ## C Signature
// ```
// Nucleus_Status
// Nucleus_getMediaContext
//   (
//       Nucleus_MediaContext **mediaContext
//   )
// ```
// ## Parameters
// - `mediaContext` a pointer to a `(Nucleus_MediaContext *)` variable
// ## Description
// If this function succeeds `*mediaContext` is assigned the address of a `Nucleus_MediaContext` object.
// This function fails iff `mediaContext` is a null pointer or the `Nucleus_MediaContext` singleon does not exist.
// `Nucleus_Status_InvalidArgument` is returned in the former case and `Nucleus_Status_NotExists` is returned in the latter case.

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_get
    (
        Nucleus_MediaContext **mediaContext
    );

// # `Nucleus_MediaContext_startup`
// *Startup the `Nucleus_MediaContext` singleton.*
// ## C Signature
// ```
// Nucleus_Status
// Nucleus_MediaContext_startup
//     (
//     );
// ```
// ## Description
// If the `Nucleus_MediaContext` singleton does exist, `Nucleus_Status_Exists` is returned.
// If it does not exist, then it is created.
// If the creation fails, a non-zero status code is returned.
Nucleus_Media_Library_Export Nucleus_Status
Nucleus_MediaContext_initialize
    (
    );
 
// # `Nucleus_MediaContext_shutdown`
// *Shutdown the `Nucleus_MediaContext` singleton.*
// ## C Signature
// ```
// Nucleus_Status
// Nucleus_MediaContext_uninitialize
//     (
//     );
// ```
// ## Description
// If the `Nucleus_MediaContext` singleton does not exist, `Nucleus_Status_NotExists` is returned.
// If it does exist, it is destroyed.
Nucleus_Media_Library_Export Nucleus_Status
Nucleus_MediaContext_uninitialize
    (
    );

// Register an audio system factory.
// If an equivalent factory is already registered, #Nucleus_Status_AlreadyExists is returned.
Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_registerAudioSystemFactory
    (
        Nucleus_MediaContext *mediaContext,
        Nucleus_Media_AudioSystemFactory *audioSystemFactory
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_getAudioSystemFactories
    (
        Nucleus_MediaContext *mediaContext,
        Nucleus_ObjectEnumerator **enumerator
    );

// Register a video system factory.
// If an equivalent factory is already registered, #Nucleus_Status_AlreadyExists is returned.
Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_registerVideoSystemFactory
    (
        Nucleus_MediaContext *mediaContext,
        Nucleus_Media_VideoSystemFactory *videoSystemFactory
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_getVideoSystemFactories
    (
        Nucleus_MediaContext *mediaContext,
        Nucleus_ObjectEnumerator **enumerator  
    );

Nucleus_NonNull(1) Nucleus_Status
Nucleus_MediaContext_startup
    (
        Nucleus_MediaContext *context,
        Nucleus_Status(*selectVideoSystemFactory)(Nucleus_Media_VideoSystemFactory **factory),
        Nucleus_Status(*selectVideoSystemConfiguration)(Nucleus_ObjectEnumerator *enumerator,
                                                        Nucleus_Media_VideoSystemConfiguration **configuration),
        Nucleus_Status(*selectAudioSystemFactory)(Nucleus_Media_AudioSystemFactory **factory),
        Nucleus_Status(*selectAudioSystemConfiguration)(Nucleus_ObjectEnumerator *enumerator,
                                                        Nucleus_Media_AudioSystemConfiguration **configuration)
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_shutdown
    (
        Nucleus_MediaContext *context
    );
