// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.Metal/VideoSystemWindow.h"
#include "Nucleus.Media.Plugin.Metal/VideoSystem.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_Metal_Export,
                            "Nucleus.Media.Plugin.Metal.VideoSystemWindow",
                            Nucleus_Media_Plugin_Metal_VideoSystemWindow,
                            Nucleus_Media_VideoSystemWindow)
    
Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_Metal_VideoSystemWindow_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_Metal_VideoSystemWindow_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_Metal_VideoSystemWindow *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_Metal_VideoSystemWindow_construct
    (
        Nucleus_Media_Plugin_Metal_VideoSystemWindow *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_Plugin_Metal_VideoSystemWindow_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Media_VideoSystemWindow_construct(NUCLEUS_MEDIA_VIDEOSYSTEMWINDOW(self));
    if (Nucleus_Unlikely(status)) return status;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineDefaultCreate(Nucleus_Media_Plugin_Metal_VideoSystemWindow)
