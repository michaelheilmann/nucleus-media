// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.Direct3D/VideoSystemFactory.h"

#include "Nucleus.Media.Plugin.Direct3D/getVideoSystemConfigurations.h"
#include "Nucleus.Media.Plugin.Direct3D/VideoSystem.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_Direct3D_Export,
                            u8"Nucleus.Media.Plugin.Direct3D.VideoSystemFactory",
                            Nucleus_Media_Plugin_Direct3D_VideoSystemFactory,
                            Nucleus_Media_VideoSystemFactory)

Nucleus_NonNull() static Nucleus_Status
getSystemName
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory *self,
        Nucleus_String **systemName
    );

Nucleus_NonNull() static Nucleus_Status
createSystem
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory *self,
        Nucleus_Media_VideoSystem **system
    );

Nucleus_NonNull() static Nucleus_Status
getConfigurations
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory *self,
        Nucleus_ObjectArray **configurations
    );
    
Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory_Class *dispatch
    )
{
    NUCLEUS_MEDIA_VIDEOSYSTEMFACTORY_CLASS(dispatch)->createSystem = (Nucleus_Status(*)(Nucleus_Media_VideoSystemFactory *, Nucleus_Media_VideoSystem **))&createSystem;
    NUCLEUS_MEDIA_VIDEOSYSTEMFACTORY_CLASS(dispatch)->getSystemName = (Nucleus_Status(*)(Nucleus_Media_VideoSystemFactory *, Nucleus_String **))&getSystemName;
    NUCLEUS_MEDIA_VIDEOSYSTEMFACTORY_CLASS(dispatch)->getConfigurations = (Nucleus_Status(*)(Nucleus_Media_VideoSystemFactory *, Nucleus_ObjectArray **))&getConfigurations;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory *self
    )
{
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(self->systemName));
    self->systemName = NULL;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
getSystemName
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory *self,
        Nucleus_String **systemName
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Object_incrementReferenceCount(NUCLEUS_OBJECT(self->systemName));
    *systemName = self->systemName;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
createSystem
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory *self,
        Nucleus_Media_VideoSystem **system
    )
{
    if (Nucleus_Unlikely(!self || !system)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Media_Plugin_Direct3D_VideoSystem_create((Nucleus_Media_Plugin_Direct3D_VideoSystem **)system);
}

Nucleus_NonNull() static Nucleus_Status
getConfigurations
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemFactory *self,
        Nucleus_ObjectArray **configurations
    )
{
    if (Nucleus_Unlikely(!self || !configurations)) return Nucleus_Status_InvalidArgument;
    //
    Nucleus_Status status;
    Nucleus_ObjectArray *temporary;
    //
    status = Nucleus_ObjectArray_create(&temporary);
    if (Nucleus_Unlikely(status))
    {
        return status;
    }
    //
    status = getVideoSystemConfigurations(temporary);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(temporary));
        return status;
    }
    //
    *configurations = temporary;
    //
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
    status = Nucleus_Media_VideoSystemFactory_construct(NUCLEUS_MEDIA_VIDEOSYSTEMFACTORY(self));
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_String_create(&self->systemName, u8"Direct3D Video System");
    if (Nucleus_Unlikely(status)) return status;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineDefaultCreate(Nucleus_Media_Plugin_Direct3D_VideoSystemFactory)
