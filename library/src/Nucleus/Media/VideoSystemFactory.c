// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Media/VideoSystemFactory.h"

#include "Nucleus/Media/Context.h"
#include "Nucleus/Memory.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            "Nucleus.Media.VideoSystemFactory",
                            Nucleus_Media_VideoSystemFactory,
                            Nucleus_Object)

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_VideoSystemFactory_Class *dispatch
    )
{
    dispatch->getSystemName = NULL;
    dispatch->createSystem = NULL;
	dispatch->getConfigurations = NULL;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_VideoSystemFactory_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_VideoSystemFactory *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemFactory_construct
    (
        Nucleus_Media_VideoSystemFactory *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_VideoSystemFactory_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Object_construct(NUCLEUS_OBJECT(self));
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemFactory_getSystemName
    (
        Nucleus_Media_VideoSystemFactory *self,
        Nucleus_String **systemName
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    return getDispatch(self)->getSystemName(self, systemName);
}

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemFactory_createSystem
    (
        Nucleus_Media_VideoSystemFactory *self,
        Nucleus_Media_VideoSystem **system
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    return getDispatch(self)->createSystem(self, system);
}

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemFactory_getConfigurations
    (
        Nucleus_Media_VideoSystemFactory *self,
        Nucleus_ObjectArray **configurations
	)
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    return getDispatch(self)->getConfigurations(self, configurations);
}
