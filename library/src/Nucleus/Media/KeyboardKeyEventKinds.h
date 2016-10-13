/// @file Nucleus/Media/KeyboardKeyEventKinds.h
/// @brief Kinds of keyboard key events.
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

/// @ingroup media
/// @brief Enumeration of the kinds of keyboard key events.
typedef enum Nucleus_KeyboardKeyEventKinds
{
#define Alias(aliased,alias) Nucleus_KeyboardKeyEventKinds_##alias = Nucleus_KeyboardKeyEventKinds_##aliased,
#define Define(name,value,description) Nucleus_KeyboardKeyEventKinds_##name = value,
#include "Nucleus/Media/KeyboardKeyEventKinds.in"
#undef Define
#undef Alias
} Nucleus_KeyboardKeyEventKinds;

/// @ingroup media
/// @brief Return a human-readable, static string describing a keyboard key event kind.
/// @param kind the event kind
/// @param [out] string a pointer to a (const char *) variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
/// @post
/// - On success: @a *string was assigned a pointer to a static constant string
/// - On failure: @a string was not dereferenced
Nucleus_NonNull(2) Nucleus_Status
Nucleus_KeyboardKeyEventKinds_toString
    (
        Nucleus_KeyboardKeyEventKinds kind,
        const char **string
    );
