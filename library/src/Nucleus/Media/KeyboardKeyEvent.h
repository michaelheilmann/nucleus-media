/// @file Nucleus/Media/KeyboardKeyEvent.h
/// @brief Keyboard key events.
#pragma once

#include "Nucleus/Media/Event.h"

#include "Nucleus/Media/KeyboardKeys.h"
#include "Nucleus/Media/KeyboardKeyEventKinds.h"

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.KeyboardKeyEvent",
                             Nucleus_KeyboardKeyEvent,
                             Nucleus_Event)
#define NUCLEUS_KEYBOARDKEYEVENT(p) ((Nucleus_KeyboardKeyEvent *)(p))
#define NUCLEUS_KEYBOARDKEYEVENT_CLASS(p) ((Nucleus_KeyboardKeyEvent_Class *)(p))

struct Nucleus_KeyboardKeyEvent_Class
{
    Nucleus_Event_Class parent;
}; // struct Nucleus_KeyboardKeyEvent_Class

struct Nucleus_KeyboardKeyEvent
{
    Nucleus_Event parent;
    Nucleus_KeyboardKeyEventKinds kind; ///< @brief The kind of this keyboardKey event.
    Nucleus_KeyboardKeys key;
    int modifiers;
}; // struct Nucleus_KeyboardKeyEvent

/// @ingroup media
/// @brief Construct an keyboard key event.
/// @param keyboardKeyEvent a pointer to an keyboard key event
/// @param kind the kind of the keyboard key event
/// @return #Nucleus_Status_Success on success, a non-zero value on failure
Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_KeyboardKeyEvent_construct
    (
        Nucleus_KeyboardKeyEvent *keyboardKeyEvent,
        Nucleus_KeyboardKeyEventKinds kind,
        Nucleus_KeyboardKeys key,
        int modifiers
    );

/// @ingroup media
/// @brief Create an keyboard key event.
/// @param [out] keyboardKeyEvent a pointer to an @a (Nucleus_KeyboardKeyEvent *) variable
/// @param kind the kind of the keyboardKey event
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_KeyboardKeyEvent_create
    (
        Nucleus_KeyboardKeyEvent **keyboardKeyEvent,
        Nucleus_KeyboardKeyEventKinds kind,
        Nucleus_KeyboardKeys key,
        int modifiers
    );

/// @ingroup media
/// @brief Get the kind of a keyboard key event.
/// @param keyboardKeyEvent a pointer to an keyboard key event
/// @param [out] kind a pointer to a @a Nucleus_KeyboardKeyEventKinds variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_KeyboardKeyEvent_getKeyboardKeyEventKind
    (
        Nucleus_KeyboardKeyEvent *keyboardKeyEvent,
        Nucleus_KeyboardKeyEventKinds *kind
    );
