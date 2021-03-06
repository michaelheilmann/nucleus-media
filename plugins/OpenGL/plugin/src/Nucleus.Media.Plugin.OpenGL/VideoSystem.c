// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.OpenGL/VideoSystem.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_OpenGL_Export,
                            u8"Nucleus.Media.Plugin.OpenGL.VideoSystem",
                            Nucleus_Media_Plugin_OpenGL_VideoSystem,
                            Nucleus_Media_VideoSystem)

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystem_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystem_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystem *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_VideoSystem_construct
    (
        Nucleus_Media_Plugin_OpenGL_VideoSystem *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    //
    Nucleus_Type *type;
    Nucleus_Status status;
    //
    status = Nucleus_Media_Plugin_OpenGL_VideoSystem_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    //
    status = Nucleus_Media_VideoSystem_construct(NUCLEUS_MEDIA_VIDEOSYSTEM(self));
    if (Nucleus_Unlikely(status)) return status;
    //
    NUCLEUS_OBJECT(self)->type = type;
    //
    return Nucleus_Status_Success;
}
