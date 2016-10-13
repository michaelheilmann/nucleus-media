// Copyright (c) 2018 Michael Heilmann

/// @file Nucleus/Media/MouseButtonEventKinds.h
/// @brief Kinds of mouse button events.
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"

/// @ingroup media
/// @brief Enumeration of the kinds of mouse button events.
typedef enum Nucleus_MousePointerEventKinds
{
#define Alias(aliased,alias) Nucleus_MousePointerEventKinds_##alias = Nucleus_MousePointerEventKinds_##aliased,
#define Define(name,value,description) Nucleus_MousePointerEventKinds_##name = value,
#include "Nucleus/Media/MousePointerEventKinds.in"
#undef Define
#undef Alias
} Nucleus_MousePointerEventKinds;

/// @ingroup media
/// @brief Return a human-readable, static string describing a mouse pointer event kind.
/// @param kind the event kind
/// @param [out] string a pointer to a (const char *) variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
/// @post
/// - On success: @a *string was assigned a pointer to a static constant string
/// - On failure: @a string was not dereferenced
Nucleus_NonNull(2) Nucleus_Status
Nucleus_MousePointerEventKinds_toString
    (
        Nucleus_MousePointerEventKinds kind,
        const char **string
    );