/// @file Nucleus/Media/EventKinds.h
/// @brief Kinds of events.
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

/// @ingroup media
/// @brief Enumeration of the kinds of events.
typedef enum Nucleus_EventKinds
{
#define Alias(aliased,alias) Nucleus_EventKinds_##alias = Nucleus_EventKinds_##aliased,
#define Define(name,value,description) Nucleus_EventKinds_##name = value,
#include "Nucleus/Media/EventKinds.in"
#undef Define
#undef Alias
} Nucleus_EventKinds;

/// @ingroup media
/// @brief Return a human-readable, static string describing an event kind.
/// @param kind the event kind
/// @param [out] string a pointer to a (const char *) variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
/// @post
/// - On success: @a *string was assigned a pointer to a static constant string
/// - On failure: @a string was not dereferenced
Nucleus_NonNull(2) Nucleus_Status
Nucleus_EventKinds_toString
    (
        Nucleus_EventKinds kind,
        const char **string
    );
