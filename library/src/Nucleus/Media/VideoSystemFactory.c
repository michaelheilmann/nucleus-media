// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Media/VideoSystemFactory.h"

#include "Nucleus/Media/Context.h"
#include "Nucleus/Memory.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            "Nucleus.VideoSystemFactory",
                            Nucleus_VideoSystemFactory,
                            Nucleus_Object)

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_VideoSystemFactory_Class *dispatch
    )
{
    dispatch->getName = NULL;
    dispatch->create = NULL;
    return Nucleus_Status_Success;
}

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_VideoSystemFactory *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_VideoSystemFactory_construct
    (
        Nucleus_VideoSystemFactory *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_VideoSystemFactory_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Object_construct(NUCLEUS_OBJECT(self));
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}
