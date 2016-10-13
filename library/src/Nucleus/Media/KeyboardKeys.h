/// @file Nucleus/Media/KeyboardKeys.h
/// @brief Keyboard keys.
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

/// @ingroup Media
/// @brief Enumeration of keyboard keys.
typedef enum Nucleus_KeyboardKeys
{
    #define Alias(aliased,alias) Nucleus_KeyboardKeys_##alias = Nucleus_KeyboardKeys_##aliased,
    #define Define(name,value,description) Nucleus_KeyboardKeys_##name = value,
    #include "Nucleus/Media/KeyboardKeys.in"
    #undef Define
    #undef Alias
} Nucleus_KeyboardKeys;

/// @ingroup Media
/// @brief Return a human-readable, static string describing a keyboard key.
/// @param key the keyboard key
/// @param [out] string a pointer to a (const char *) variable
/// @return #Nucleus_Status_Success, a non-zero status code on failure
/// @post
/// - On success: @a *string was assigned a pointer to a static constant string
/// - On failure: @a string was not dereferenced
Nucleus_NonNull(2) Nucleus_Status
Nucleus_KeyboardKeys_toString
    (
        Nucleus_KeyboardKeys key,
        const char **string
    );
