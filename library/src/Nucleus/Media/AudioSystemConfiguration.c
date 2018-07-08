// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Media/AudioSystemConfiguration.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            u8"Nucleus.Media.AudioSystemConfiguration",
                            Nucleus_Media_AudioSystemConfiguration,
                            Nucleus_Object)

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_AudioSystemConfiguration_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_AudioSystemConfiguration_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull(1) static Nucleus_Status
destruct
    (
        Nucleus_Media_AudioSystemConfiguration *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_AudioSystemConfiguration_construct
    (
        Nucleus_Media_AudioSystemConfiguration *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_AudioSystemConfiguration_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Object_construct(NUCLEUS_OBJECT(self));
    if (Nucleus_Unlikely(status)) return status;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineDefaultCreate(Nucleus_Media_AudioSystemConfiguration)
