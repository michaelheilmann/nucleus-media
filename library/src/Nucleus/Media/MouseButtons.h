/// @file Nucleus/Media/MouseButtons.h
/// @brief Mouse buttons.
#pragma once

#include "Nucleus/Annotations.h"

/// @ingroup Media
/// @brief Enumeration of mouse buttons.
typedef enum Nucleus_MouseButtons
{
    #define Alias(aliased,alias) Nucleus_MouseButtons_##alias = Nucleus_MouseButtons_##aliased,
    #define Define(name,value,description) Nucleus_MouseButtons_##name = value,
    #include "Nucleus/Media/MouseButtons.in"
    #undef Define
    #undef Alias
} Nucleus_MouseButtons;

/// @ingroup Media
/// @brief Return a human-readable, static string describing a mouse button.
/// @param button the mouse button
/// @param [out] string a pointer to a (const char *) variable
/// @return @a 0 on success, a non-zero value on failure
/// @post
/// - On success: @a *string was assigned a pointer to a static constant string
/// - On failure: @a string was not dereferenced
Nucleus_NonNull(2) int
Nucleus_MouseButtons_toString
    (
        Nucleus_MouseButtons button,
        const char **string
    );
