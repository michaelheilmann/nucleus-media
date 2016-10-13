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

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
constructDispatch
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

Nucleus_NonNull(1) Nucleus_Status
Nucleus_MouseButtonEvent_create
    (
        Nucleus_MouseButtonEvent **mouseButtonEvent,
        Nucleus_MouseButtonEventKinds kind,
        Nucleus_MouseButtons button,
        int x,int y,
        int modifiers
    )
{
    if (Nucleus_Unlikely(!mouseButtonEvent)) return Nucleus_Status_InvalidArgument;
    //
    Nucleus_Status status;
    Nucleus_MouseButtonEvent *temporary;
    //
    status = Nucleus_Object_allocate((Nucleus_Object **)&temporary,
                                     sizeof(Nucleus_MouseButtonEvent));
    if (Nucleus_Unlikely(status)) return status;
    //
    status = Nucleus_MouseButtonEvent_construct(temporary, kind, button, x, y, modifiers);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(temporary));
        return status;
    }
    //
    *mouseButtonEvent = temporary;
    //
    return Nucleus_Status_Success;
}
