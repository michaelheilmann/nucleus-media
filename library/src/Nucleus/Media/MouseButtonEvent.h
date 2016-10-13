/// @file Nucleus/Media/MouseButtonEvent.h
/// @brief Mouse button events.
#pragma once

#include "Nucleus/Media/Event.h"

#include "Nucleus/Media/MouseButtons.h"
#include "Nucleus/Media/MouseButtonEventKinds.h"

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.MouseButtonEvent",
                             Nucleus_MouseButtonEvent,
                             Nucleus_Event)
#define NUCLEUS_MOUSEBUTTONEVENT(p) ((Nucleus_MouseButtonEvent *)(p))
#define NUCLEUS_MOUSEBUTTONEVENT_CLASS(p) ((Nucleus_MouseButtonEvent_Class *)(p))

struct Nucleus_MouseButtonEvent_Class
{
    Nucleus_Event_Class parent;
}; // struct Nucleus_MouseButtonEvent_Class

struct Nucleus_MouseButtonEvent
{
    Nucleus_Event event;
    Nucleus_MouseButtonEventKinds kind; ///< @brief The kind of the mouse button event.
    Nucleus_MouseButtons button; ///< @brief The button which was pressed or released.
    int x, y; ///< @brief The position at which the mouse button was pressed or released.
    int modifiers; ///< @brief The input modifiers.
}; // struct Nucleus_MouseButtonEvent

/// @brief Construct a mouse button event.
/// @param mouseButtonEvent a pointer to a mouse button event
/// @param kind the kind of the mouse button event
/// @param button the mouse button
/// @param x, y the position at which the mouse button was pressed or released
/// @param modifiers the input modifiers
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_MouseButtonEvent_construct
    (
        Nucleus_MouseButtonEvent *mouseButtonEvent,
        Nucleus_MouseButtonEventKinds kind,
        Nucleus_MouseButtons button,
        int x,
        int y,
        int modifiers
    );

/// Create a mouse button event.
/// @param [out] mouseButtonEvent a pointer to a Nucleus_MouseButtonEvent pointer
/// @param kind the kind of the mouse button event
/// @param button the mouse button
/// @param x, y the position at which the mouse button was pressed or released
/// @param modifiers the input modifiers
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_MouseButtonEvent_create
    (
        Nucleus_MouseButtonEvent **mouseButtonEvent,
        Nucleus_MouseButtonEventKinds kind,
        Nucleus_MouseButtons button,
        int x,
        int y,
        int modifiers
    );
