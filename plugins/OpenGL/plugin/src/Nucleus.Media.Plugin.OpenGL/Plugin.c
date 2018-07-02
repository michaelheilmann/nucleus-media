// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.OpenGL/Plugin.h"
#include "Nucleus/Media/Context.h"
#include "Nucleus.Media.Plugin.OpenGL/VideoSystemFactory.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_OpenGL_Export,
                            "Nucleus.Media.Plugin.OpenGL.Plugin",
                            Nucleus_Media_Plugin_OpenGL_Plugin,
                            Nucleus_Media_Plugin)

Nucleus_NonNull() static Nucleus_Status
startup
    (
        Nucleus_Media_Plugin_OpenGL_Plugin *self
    );
    
Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
shutdown
    (
        Nucleus_Media_Plugin_OpenGL_Plugin *self
    );

Nucleus_NonNull() static Nucleus_Status
getName
    (
        Nucleus_Media_Plugin_OpenGL_Plugin *self,
        Nucleus_String **name
    );

Nucleus_NonNull() static Nucleus_Status
startup
    (
        Nucleus_Media_Plugin_OpenGL_Plugin *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    //
    Nucleus_MediaContext *context;
    status = Nucleus_MediaContext_get(&context);
    if (Nucleus_Unlikely(status)) return status;
    //
    Nucleus_Media_Plugin_OpenGL_VideoSystemFactory *factory;
    status = Nucleus_Media_Plugin_OpenGL_VideoSystemFactory_create(&factory);
    if (Nucleus_Unlikely(status)) return status;
    //
    status = Nucleus_MediaContext_registerVideoSystemFactory(context, NUCLEUS_MEDIA_VIDEOSYSTEMFACTORY(factory));
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
    if (Nucleus_Unlikely(status))
    {
        return status;
    }
    //
    return Nucleus_Status_Success;
}

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
shutdown
    (
        Nucleus_Media_Plugin_OpenGL_Plugin *self
    )
{
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
getName
    (
        Nucleus_Media_Plugin_OpenGL_Plugin *self,
        Nucleus_String **name
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Object_incrementReferenceCount(NUCLEUS_OBJECT(self->name));
    *name = self->name;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_OpenGL_Plugin_Class *dispatch
    )
{
    NUCLEUS_MEDIA_PLUGIN_CLASS(dispatch)->startup = (Nucleus_NonNull() Nucleus_Status (*)(Nucleus_Media_Plugin *))&startup;
    NUCLEUS_MEDIA_PLUGIN_CLASS(dispatch)->shutdown = (Nucleus_AlwaysSucceed() Nucleus_NonNull() Nucleus_Status (*)(Nucleus_Media_Plugin *))&shutdown;
    NUCLEUS_MEDIA_PLUGIN_CLASS(dispatch)->getName = (Nucleus_NonNull() Nucleus_Status (*)(Nucleus_Media_Plugin *, Nucleus_String **))&getName;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_OpenGL_Plugin_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_OpenGL_Plugin *self
    )
{
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(self->name));
    self->name = NULL;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_Plugin_construct
    (
        Nucleus_Media_Plugin_OpenGL_Plugin *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    //
	Nucleus_Type *type;
    Nucleus_Status status;
	//
    status = Nucleus_Media_Plugin_OpenGL_Plugin_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    //
	status = Nucleus_Media_Plugin_construct(NUCLEUS_MEDIA_PLUGIN(self));
    if (Nucleus_Unlikely(status)) return status;
    //
    status = Nucleus_String_create(&self->name, u8"Nucleus: Media OpenGL Plugin");
    if (Nucleus_Unlikely(status)) return status;
    //
    NUCLEUS_OBJECT(self)->type = type;
    //
	return Nucleus_Status_Success;
}

Nucleus_DefineDefaultCreate(Nucleus_Media_Plugin_OpenGL_Plugin)
