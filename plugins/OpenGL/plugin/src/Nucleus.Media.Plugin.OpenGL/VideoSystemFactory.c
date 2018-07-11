// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.OpenGL/VideoSystemFactory.h"
#include "Nucleus.Media.Plugin.OpenGL/VideoSystem.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) 

    #include "Nucleus.Media.Plugin.OpenGL/GLX/getVideoSystemConfigurations.h"
    #include "Nucleus.Media.Plugin.OpenGL/GLX/VideoSystem.h"

#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

    #include "Nucleus.Media.Plugin.OpenGL/WGL/getVideoSystemConfigurations.h"
    #include "Nucleus.Media.Plugin.OpenGL/WGL/VideoSystem.h"

#else

    #error("environment not supported)

#endif

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_OpenGL_Export,
                            u8"Nucleus.Media.Plugin.OpenGL.VideoSystemFactory",
                            Nucleus_Media_Plugin_OpenGL_VideoSystemFactory,
                            Nucleus_Media_VideoSystemFactory)

Nucleus_NonNull() static Nucleus_Status
getSystemName
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemFactory *self,
        Nucleus_String **systemName
    );

Nucleus_NonNull() static Nucleus_Status
createSystem
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemFactory *self,
        Nucleus_Media_VideoSystem **system
    );

Nucleus_NonNull() static Nucleus_Status
getConfigurations
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemFactory *self,
        Nucleus_ObjectArray **configurations
    );

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemFactory_Class *dispatch
    )
{
    NUCLEUS_MEDIA_VIDEOSYSTEMFACTORY_CLASS(dispatch)->createSystem = (Nucleus_Status (*)(Nucleus_Media_VideoSystemFactory *, Nucleus_Media_VideoSystem **))&createSystem;
    NUCLEUS_MEDIA_VIDEOSYSTEMFACTORY_CLASS(dispatch)->getSystemName = (Nucleus_Status (*)(Nucleus_Media_VideoSystemFactory *, Nucleus_String **))&getSystemName;
    NUCLEUS_MEDIA_VIDEOSYSTEMFACTORY_CLASS(dispatch)->getConfigurations = (Nucleus_Status (*)(Nucleus_Media_VideoSystemFactory *, Nucleus_ObjectArray **))&getConfigurations;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemFactory_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemFactory *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
getSystemName
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemFactory *self,
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
        Nucleus_Media_Plugin_OpenGL_VideoSystemFactory *self,
        Nucleus_Media_VideoSystem **system
    )
{
    if (Nucleus_Unlikely(!self || !system)) return Nucleus_Status_InvalidArgument;
#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) 
    return Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem_create((Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem **)system);
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    return Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem_create((Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem **)system);
#else
    #error("environment not supported)
#endif
}

Nucleus_NonNull() static Nucleus_Status
getConfigurations
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemFactory *self,
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
Nucleus_Media_Plugin_OpenGL_VideoSystemFactory_construct
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystemFactory *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_Plugin_OpenGL_VideoSystemFactory_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Media_VideoSystemFactory_construct(NUCLEUS_MEDIA_VIDEOSYSTEMFACTORY(self));
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_String_create(&self->systemName, u8"OpenGL Video System");
    if (Nucleus_Unlikely(status)) return status;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineDefaultCreate(Nucleus_Media_Plugin_OpenGL_VideoSystemFactory)
