/// @file Nucleus/Media/ApplicationEvent.c
/// @brief Application events.
#include "Nucleus/Media/ApplicationEvent.h"
#include "Nucleus/Memory.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            u8"Nucleus.ApplicationEvent",
                            Nucleus_ApplicationEvent,
                            Nucleus_Event)

Nucleus_AlwaysSucceed() Nucleus_NonNull(1) static Nucleus_Status
destruct
    (
        Nucleus_ApplicationEvent *applicationEvent
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_ApplicationEvent_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_ApplicationEvent_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull(1) Nucleus_Status
Nucleus_ApplicationEvent_construct
    (
        Nucleus_ApplicationEvent *self,
        Nucleus_ApplicationEventKinds kind
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_ApplicationEvent_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Event_construct(NUCLEUS_EVENT(self), Nucleus_EventKinds_ApplicationEvent);
    if (Nucleus_Unlikely(status)) return status;
    self->kind = kind;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineCreate(Nucleus_ApplicationEvent,
                     Nucleus_Parameters(Nucleus_ApplicationEventKinds kind),
                     Nucleus_Arguments(kind))

Nucleus_NonNull(1) Nucleus_Status
Nucleus_ApplicationEvent_getKind
    (
        Nucleus_ApplicationEvent *applicationEvent,
        Nucleus_ApplicationEventKinds *kind
    )
{
    if (Nucleus_Unlikely(!applicationEvent || !kind)) return Nucleus_Status_InvalidArgument;
    *kind = applicationEvent->kind;
    return Nucleus_Status_Success;
}
