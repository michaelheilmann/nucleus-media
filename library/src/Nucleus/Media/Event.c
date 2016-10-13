/// @file Nucleus/Media/Event.c
/// @brief Event basis.
#include "Nucleus/Media/Event.h"

#include "Nucleus/Memory.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            "Nucleus.Event",
                            Nucleus_Event,
                            Nucleus_Object)

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Event_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull(1) static Nucleus_Status
destruct
    (
        Nucleus_Event *event
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Event_construct
    (
        Nucleus_Event *event,
        Nucleus_EventKinds kind
    )
{
    if (Nucleus_Unlikely(!event)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Event_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Object_construct(NUCLEUS_OBJECT(event));
    if (Nucleus_Unlikely(status)) return status;
    event->kind = kind;
    NUCLEUS_OBJECT(event)->type = type;
    return Nucleus_Status_Success;
}
