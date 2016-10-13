// Copyright (c) 2018 Michael Heilmann
#include "VideoSystemFactory.h"

#include "Nucleus/Media/Context.h"
#include "Nucleus/Memory.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_Direct3D_Export,
                 "Nucleus.Media.Plugin.Direct3D.VideoSystemFactory",
                 Nucleus_Media_Plugin_Direct3D_VideoSystemFactory,
                 Nucleus_VideoSystemFactory)


Nucleus_NonNull() static Nucleus_Status
getName
    (
        Nucleus_VideoSystemFactory *self,
        Nucleus_String **name
    );

Nucleus_NonNull() static Nucleus_Status
create
    (
        Nucleus_VideoSystemFactory *self,
        Nucleus_VideoSystem **videoSystem
    );
    
Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory_Class *dispatch
    )
{
    NUCLEUS_VIDEOSYSTEMFACTORY_CLASS(dispatch)->create = &create;
    NUCLEUS_VIDEOSYSTEMFACTORY_CLASS(dispatch)->getName = NULL;
    return Nucleus_Status_Success;
}

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory *self
    )
{
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(self->name));
    self->name = NULL;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
getName
    (
        Nucleus_VideoSystemFactory *self,
        Nucleus_String **name
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Object_incrementReferenceCount(NUCLEUS_OBJECT(self->name));
    *name = self->name;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
create
    (
        Nucleus_VideoSystemFactory *self,
        Nucleus_VideoSystem **videoSystem
    )
{
    if (Nucleus_Unlikely(!self || !videoSystem)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_Direct3D_VideoSystemFactory_construct
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_Plugin_Direct3D_VideoSystemFactory_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_VideoSystemFactory_construct(NUCLEUS_VIDEOSYSTEMFACTORY(self));
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_String_create(&self->name, u8"Direct3D Renderer");
    if (Nucleus_Unlikely(status)) return status;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_Direct3D_VideoSystemFactory_create
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory **videoSystemFactory
    )
{
    // validate arguments
    if (Nucleus_Unlikely(!videoSystemFactory)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_Media_Plugin_Direct3D_VideoSystemFactory *temporary;
    // allocate
    status = Nucleus_Object_allocate((Nucleus_Object **)&temporary,
                                     sizeof(Nucleus_Media_Plugin_Direct3D_VideoSystemFactory));
    if (Nucleus_Unlikely(status)) return status;
    // construct
    status = Nucleus_Media_Plugin_Direct3D_VideoSystemFactory_construct(temporary);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(temporary));
        return status;
    }
    // assign result
    *videoSystemFactory = temporary;
    // return with success
    return Nucleus_Status_Success;
}
