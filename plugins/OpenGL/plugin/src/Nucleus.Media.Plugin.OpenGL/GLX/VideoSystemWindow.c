// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.OpenGL/GLX/VideoSystemWindow.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_OpenGL_Export,
                            u8"Nucleus.Media.Plugin.OpenGL.GLX.VideoSystemWindow",
                            Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow,
                            Nucleus_Media_Plugin_OpenGL_VideoSystemWindow)
    
Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow *self
    )
{
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(self->videoSystem));
    self->videoSystem = NULL;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow_construct
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow *self,
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem *videoSystem
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Media_Plugin_OpenGL_VideoSystemWindow_construct(NUCLEUS_MEDIA_PLUGIN_OPENGL_VIDEOSYSTEMWINDOW(self));
    if (Nucleus_Unlikely(status)) return status;
    self->videoSystem = videoSystem;
    Nucleus_Object_incrementReferenceCount(NUCLEUS_OBJECT(videoSystem));
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineCreate(Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow,
                     Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem *videoSystem,
                     videoSystem)
