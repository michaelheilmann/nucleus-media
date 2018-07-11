// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.OpenGL/GLX/VideoSystem.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)
    
#include "Nucleus.Media.Plugin.OpenGL/GLX/VideoSystemWindow.h"

Nucleus_NonNull() static Nucleus_Status
createWindow
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem *self,
        Nucleus_Media_VideoSystemWindow **window
    );
    
Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_OpenGL_Export,
                            u8"Nucleus.Media.Plugin.OpenGL.GLX.VideoSystem",
                            Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem,
                            Nucleus_Media_Plugin_OpenGL_VideoSystem)

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem_Class *dispatch
    )
{
    NUCLEUS_MEDIA_VIDEOSYSTEM_CLASS(dispatch)->createWindow = (Nucleus_NonNull() Nucleus_Status (*)(Nucleus_Media_VideoSystem *, Nucleus_Media_VideoSystemWindow **))&createWindow;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem *self
    )
{
    XCloseDisplay(self->display);
    self->display = NULL;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
createWindow
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem *self,
        Nucleus_Media_VideoSystemWindow **window
    )
{
    if (Nucleus_Unlikely(!self || !window)) return Nucleus_Status_InvalidArgument;
    //
    Nucleus_Status status;
    Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow *temporary;
    //
    status = Nucleus_Media_Plugin_OpenGL_GLX_VideoSystemWindow_create(&temporary, self);
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
Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem_construct
    (
        Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    //
    status = Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    //
    status = Nucleus_Media_Plugin_OpenGL_VideoSystem_construct(NUCLEUS_MEDIA_PLUGIN_OPENGL_VIDEOSYSTEM(self));
    if (Nucleus_Unlikely(status)) return status;
    //
    self->display = XOpenDisplay(NULL);
    if (NULL == self->display)
    {
        fprintf(stderr, u8"%s failed\n", u8"XOpenDisplay");
        return Nucleus_Status_EnvironmentFailed;
    }
    self->desktopWindow = DefaultRootWindow(self->display);
    NUCLEUS_OBJECT(self)->type = type;
    //
    return Nucleus_Status_Success;
}

Nucleus_DefineSingletonCreate(Nucleus_Media_Plugin_OpenGL_GLX_VideoSystem)

#endif
