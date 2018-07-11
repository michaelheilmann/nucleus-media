// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.OpenGL/WGL/VideoSystem.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus.Media.Plugin.OpenGL/WGL/VideoSystemWindow.h"

Nucleus_NonNull() static Nucleus_Status
createWindow
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem *self,
        Nucleus_Media_VideoSystemWindow **window
    );

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_OpenGL_Export,
                            u8"Nucleus.Media.Plugin.OpenGL.WGL.VideoSystem",
                            Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem,
                            Nucleus_Media_Plugin_OpenGL_VideoSystem)

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem_Class *dispatch
    )
{
    NUCLEUS_MEDIA_VIDEOSYSTEM_CLASS(dispatch)->createWindow = (Nucleus_NonNull() Nucleus_Status (*)(Nucleus_Media_VideoSystem *, Nucleus_Media_VideoSystemWindow **))&createWindow;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
createWindow
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem *self,
        Nucleus_Media_VideoSystemWindow **window
    )
{
    if (Nucleus_Unlikely(!self || !window)) return Nucleus_Status_InvalidArgument;
    //
    Nucleus_Status status;
    Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow *temporary;
    //
    status = Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow_create(&temporary, self);
    if (Nucleus_Unlikely(temporary))
    {
        return status;
    }
    //
    *window = NUCLEUS_MEDIA_VIDEOSYSTEMWINDOW(temporary);
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem_construct
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    //
    status = Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    //
    status = Nucleus_Media_Plugin_OpenGL_VideoSystem_construct(NUCLEUS_MEDIA_PLUGIN_OPENGL_VIDEOSYSTEM(self));
    if (Nucleus_Unlikely(status)) return status;
    //
    self->window = NULL;
    //
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineSingletonCreate(Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem)

#endif
