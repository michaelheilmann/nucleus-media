// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/Event.h"
#include "Nucleus/Media/MousePointerEventKinds.h"

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.MousePointerEvent",
                             Nucleus_MousePointerEvent,
                             Nucleus_Event)
#define NUCLEUS_MOUSEPOINTEREVENT(p) ((Nucleus_MousePointerEvent *)(p))
#define NUCLEUS_MOUSEPOINTEREVENT_CLASS(p) ((Nucleus_MousePointerEvent_Class *)(p))

struct Nucleus_MousePointerEvent_Class
{
    Nucleus_Event_Class parent;
}; // struct Nucleus_MousePointerEvent_Class

struct Nucleus_MousePointerEvent
{
    Nucleus_Event parent;
    Nucleus_MousePointerEventKinds kind; ///< @brief The kind of this mouse pointer event.
    int x, y;
    int modifiers;
};

/// @ingroup media
/// @brief Construct a mouse pointer event.
/// @param mousePointerEvent a pointer to a mouse pointer event
/// @return #Nucleus_Status_Success on success, a non-zero value on failure
Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_MousePointerEvent_construct
    (
        Nucleus_MousePointerEvent *self,
        Nucleus_MousePointerEventKinds kind,
        int x, int y, int modifiers
    );

/// @ingroup media
/// @brief Create an keyboard key event.
/// @param [out] mousePointerEvent a pointer to an @a (Nucleus_MousePointerEvent *) variable
/// @param kind the kind of the keyboardKey event
/// @param x, y the x- and y-coordinates of the mouse pointer
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_MousePointerEvent_create
    (
        Nucleus_MousePointerEvent **mousePointerEvent,
        Nucleus_MousePointerEventKinds kind,
        int x, int y,
        int modifiers
    );

/// @ingroup media
/// @brief Get the kind of an mouse pointer event.
/// @param mousePointerEvent a pointer to a mouse pointer event
/// @param [out] kind a pointer to a @a Nucleus_MousePointerEventKinds variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_MousePointerEvent_getMousePointerEventKind
    (
        Nucleus_MousePointerEvent *mousePointerEvent,
        Nucleus_MousePointerEventKinds *kind
    );
