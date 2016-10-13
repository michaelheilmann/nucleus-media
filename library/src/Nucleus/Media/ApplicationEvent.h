/// @file Nucleus/Media/ApplicationEvent.h
/// @brief Application events.
#pragma once

#include "Nucleus/Media/Event.h"
#include "Nucleus/Media/ApplicationEventKinds.h"

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.ApplicationEent",
                             Nucleus_ApplicationEvent,
                             Nucleus_Event)
#define NUCLEUS_APPLICATIONEVENT(p) ((Nucleus_ApplicationEvent *)(p))
#define NUCLEUS_APPLICATIONEVENT_CLASS(p) ((Nucleus_ApplicationEvent_Class *)(p))

struct Nucleus_ApplicationEvent_Class
{
    Nucleus_Event_Class parent;
}; // struct Nucleus_ApplicationEvent_Class


struct Nucleus_ApplicationEvent
{
    Nucleus_Event parent;
    Nucleus_ApplicationEventKinds kind; ///< @brief The kind of this application event.
}; // struct Nucleus_ApplicationEvent

/// @ingroup media
/// @brief Construct an application event.
/// @param applicationEvent a pointer to an application event
/// @param kind the kind of the application event
/// @return `Nucleus_Status_Success` on success, a non-zero status code on failure
Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_ApplicationEvent_construct
    (
        Nucleus_ApplicationEvent *applicationEvent,
        Nucleus_ApplicationEventKinds kind
    );

/// @ingroup media
/// @brief Create an application event.
/// @param [out] applicationEvent a pointer to an @a Nucleus_ApplicationEvent variable
/// @param kind the kind of the application event
/// @return @a 0 on success, a non-zero value on failure
Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_ApplicationEvent_create
    (
        Nucleus_ApplicationEvent **applicationEvent,
        Nucleus_ApplicationEventKinds kind
    );

/// @ingroup media
/// @brief Get the kind of an application event.
/// @param applicationEvent a pointer to an application event
/// @param [out] kind a pointer to a @a Nucleus_ApplicationEventKinds variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_ApplicationEvent_getKind
    (
        Nucleus_ApplicationEvent *applicationEvent,
        Nucleus_ApplicationEventKinds *kind
    );
