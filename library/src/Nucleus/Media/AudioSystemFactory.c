// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Media/AudioSystemFactory.h"

#include "Nucleus/Media/Context.h"
#include "Nucleus/Memory.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            "Nucleus.Media.AudioSystemFactory",
                            Nucleus_Media_AudioSystemFactory,
                            Nucleus_Object)

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_AudioSystemFactory_Class *dispatch
    )
{
    dispatch->getSystemName = NULL;
    dispatch->createSystem = NULL;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_AudioSystemFactory_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_AudioSystemFactory *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_AudioSystemFactory_construct
    (
        Nucleus_Media_AudioSystemFactory *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_AudioSystemFactory_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Object_construct(NUCLEUS_OBJECT(self));
    if (Nucleus_Unlikely(status)) return status;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_AudioSystemFactory_getSystemName
    (
        Nucleus_Media_AudioSystemFactory *self,
        Nucleus_String **systemName
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    return getDispatch(self)->getSystemName(self, systemName);
}

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_AudioSystemFactory_createSystem
    (
        Nucleus_Media_AudioSystemFactory *self,
        Nucleus_Media_AudioSystem **system
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    return getDispatch(self)->createSystem(self, system);
}
