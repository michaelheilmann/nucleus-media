/// @file Nucleus/Media/KeyboardKeyEvent.c
/// @brief Keyboard key events.
#include "Nucleus/Media/KeyboardKeyEvent.h"
#include "Nucleus/Memory.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            u8"Nucleus.KeyboardKeyEvent",
                            Nucleus_KeyboardKeyEvent,
                            Nucleus_Event)

Nucleus_AlwaysSucceed() Nucleus_NonNull(1) static Nucleus_Status
destruct
    (
        Nucleus_KeyboardKeyEvent *keyboardKeyEvent
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_KeyboardKeyEvent_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_KeyboardKeyEvent_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull(1) Nucleus_Status
Nucleus_KeyboardKeyEvent_construct
    (
        Nucleus_KeyboardKeyEvent *self,
        Nucleus_KeyboardKeyEventKinds kind,
        Nucleus_KeyboardKeys key,
        int modifiers
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_KeyboardKeyEvent_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Event_construct(NUCLEUS_EVENT(self), Nucleus_EventKinds_KeyboardKeyEvent);
    if (Nucleus_Unlikely(status)) return status;
    self->kind = kind;
    self->key = key;
    self->modifiers = modifiers;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineCreate(Nucleus_KeyboardKeyEvent,
                     Nucleus_Parameters(Nucleus_KeyboardKeyEventKinds kind,
					                    Nucleus_KeyboardKeys key,
								        int modifiers),
					 Nucleus_Arguments(kind,
					                   key,
									   modifiers))

Nucleus_NonNull(1) Nucleus_Status
Nucleus_KeyboardKeyEvent_getKeyboardKeyEventKind
    (
        Nucleus_KeyboardKeyEvent *keyboardKeyEvent,
        Nucleus_KeyboardKeyEventKinds *kind
    )
{
    if (Nucleus_Unlikely(!keyboardKeyEvent || !kind)) return Nucleus_Status_InvalidArgument;
    *kind = keyboardKeyEvent->kind;
    return Nucleus_Status_Success;
}
