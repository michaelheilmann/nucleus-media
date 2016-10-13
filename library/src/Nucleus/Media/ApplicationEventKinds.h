// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

/// @ingroup media
/// @brief An enumeration of the different kinds of application events.
typedef enum Nucleus_ApplicationEventKinds
{
    #define Alias(aliased,alias) Nucleus_ApplicationEventKinds_##alias = Nucleus_ApplicationEventKinds_##aliased,
    #define Define(name,value,description) Nucleus_ApplicationEventKinds_##name = value,
    #include "Nucleus/Media/ApplicationEventKinds.in"
    #undef Define
    #undef Alias
} Nucleus_ApplicationEventKinds;

/// @ingroup media
/// @brief Return a human-readable, static string describing an application event kind.
/// @param kind the application event
/// @param [out] string a pointer to a (const char *) variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
/// @post
/// - On success: @a *string was assigned a pointer to a static constant string
/// - On failure: @a string was not dereferenced
Nucleus_NonNull(2) Nucleus_Status
Nucleus_ApplicationEventKinds_toString
    (
        Nucleus_ApplicationEventKinds kind,
        const char **string
    );
