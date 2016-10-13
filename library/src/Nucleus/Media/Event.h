/// @file Nucleus/Media/Event.h
/// @brief Event basis.
#pragma once

#include "Nucleus/Media/OOP/Include.h"
#include "Nucleus/Media/EventKinds.h"

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.Event",
                             Nucleus_Event,
                             Nucleus_Object)
#define NUCLEUS_EVENT(p) ((Nucleus_Event *)(p))
#define NUCLEUS_EVENT_CLASS(p) ((Nucleus_Event_Class *)(p))

struct Nucleus_Event_Class
{
    Nucleus_Object_Class parent;
}; // struct Nucleus_Event_Class

struct Nucleus_Event
{
    Nucleus_Object parent;
    Nucleus_EventKinds kind; ///< @brief The kind of this event.
}; // struct Nucleus_Event

/// @ingroup media
/// @brief Construct an event.
/// @param event a pointer to an event
/// @param kind the kind of the event
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
Nucleus_NonNull(1) Nucleus_Status
Nucleus_Event_construct
    (
        Nucleus_Event *event,
        Nucleus_EventKinds kind
    );
