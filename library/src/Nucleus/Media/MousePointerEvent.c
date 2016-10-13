/// @file Nucleus/Media/MousePointerEvent.c
/// @brief Keyboard key events.
#include "Nucleus/Media/MousePointerEvent.h"
#include "Nucleus/Memory.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            "Nucleus.MousePointerEvent",
                            Nucleus_MousePointerEvent,
                            Nucleus_Event)

Nucleus_AlwaysSucceed() Nucleus_NonNull(1) static Nucleus_Status
destruct
    (
        Nucleus_MousePointerEvent *mousePointerEvent
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_MousePointerEvent_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull(1) Nucleus_Status
Nucleus_MousePointerEvent_construct
    (
        Nucleus_MousePointerEvent *self,
        Nucleus_MousePointerEventKinds kind,
        int x, int y,
        int modifiers
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_MousePointerEvent_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Event_construct(NUCLEUS_EVENT(self), Nucleus_EventKinds_MousePointerEvent);
    if (Nucleus_Unlikely(status)) return status;
    self->kind = kind;
    self->x = x;
    self->y = y;
    self->modifiers = modifiers;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_MousePointerEvent_create
    (
        Nucleus_MousePointerEvent **mousePointerEvent,
        Nucleus_MousePointerEventKinds kind,
        int x, int y,
        int modifiers
    )
{
    if (Nucleus_Unlikely(!mousePointerEvent)) return Nucleus_Status_InvalidArgument;
    //
    Nucleus_Status status;
    Nucleus_MousePointerEvent *temporary;
    //
    status = Nucleus_Object_allocate((Nucleus_Object **)&temporary,
                                     sizeof(Nucleus_MousePointerEvent));
    if (Nucleus_Unlikely(status)) return status;
    //
    status = Nucleus_MousePointerEvent_construct(temporary, kind, x, y, modifiers);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(temporary));
        return status;
    }
    //
    *mousePointerEvent = temporary;
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_MousePointerEvent_getMousePointerEventKind
    (
        Nucleus_MousePointerEvent *mousePointerEvent,
        Nucleus_MousePointerEventKinds *kind
    )
{
    if (Nucleus_Unlikely(!mousePointerEvent || !kind)) return Nucleus_Status_InvalidArgument;
    *kind = mousePointerEvent->kind;
    return Nucleus_Status_Success;
}
