// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.OpenAL/AudioSystem.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_OpenAL_Export,
                            u8"Nucleus.Media.Plugin.OpenAL.AudioSystem",
                            Nucleus_Media_Plugin_OpenAL_AudioSystem,
                            Nucleus_Media_AudioSystem)

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_OpenAL_AudioSystem_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_OpenAL_AudioSystem_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_OpenAL_AudioSystem *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenAL_AudioSystem_construct
    (
        Nucleus_Media_Plugin_OpenAL_AudioSystem *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_Plugin_OpenAL_AudioSystem_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Media_AudioSystem_construct(NUCLEUS_MEDIA_AUDIOSYSTEM(self));
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_String_create(&self->systemName, u8"OpenAL Audio System");
    if (Nucleus_Unlikely(status)) return status;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineDefaultCreate(Nucleus_Media_Plugin_OpenAL_AudioSystem)
