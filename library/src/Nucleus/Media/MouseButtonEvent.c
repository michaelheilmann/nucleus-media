/// @file Nucleus/Media/MouseButtonEvent.c
/// @brief Mouse button events.
#include "Nucleus/Media/MouseButtonEvent.h"
#include "Nucleus/Memory.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            "Nucleus.MouseButtonEvent",
                            Nucleus_MouseButtonEvent,
                            Nucleus_Event)

Nucleus_AlwaysSucceed() Nucleus_NonNull(1) static Nucleus_Status
destruct
    (
        Nucleus_MouseButtonEvent *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_MouseButtonEvent_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_MouseButtonEvent_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull(1) Nucleus_Status
Nucleus_MouseButtonEvent_construct
    (
        Nucleus_MouseButtonEvent *self,
        Nucleus_MouseButtonEventKinds kind,
        Nucleus_MouseButtons button,
        int x,int y,
        int modifiers
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_MouseButtonEvent_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Event_construct(NUCLEUS_EVENT(self), Nucleus_EventKinds_MouseButtonEvent);
    if (Nucleus_Unlikely(status)) return status;
    self->kind = kind;
    self->button = button;
    self->x = x;
    self->y = y;
    self->modifiers = modifiers;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineCreate(Nucleus_MouseButtonEvent,
                     Nucleus_Parameters(Nucleus_MouseButtonEventKinds kind,
					                    Nucleus_MouseButtons button,
										int x, int y,
										int modifiers),
					 Nucleus_Arguments(kind,
					                   button, x, y,
									   modifiers))
