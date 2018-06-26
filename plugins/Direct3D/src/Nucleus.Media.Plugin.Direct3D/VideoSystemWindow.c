// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.Direct3D/VideoSystemWindow.h"
#include "Nucleus.Media.Plugin.Direct3D/VideoSystem.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_Direct3D_Export,
                            "Nucleus.Media.Plugin.Direct3D.VideoSystemWindow",
                            Nucleus_Media_Plugin_Direct3D_VideoSystemWindow,
                            Nucleus_Media_VideoSystemWindow)
    
Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemWindow_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemWindow_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemWindow *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_Direct3D_VideoSystemWindow_construct
    (
        Nucleus_Media_Plugin_Direct3D_VideoSystemWindow *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_Plugin_Direct3D_VideoSystemWindow_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Media_VideoSystemWindow_construct(NUCLEUS_MEDIA_VIDEOSYSTEMWINDOW(self));
    if (Nucleus_Unlikely(status)) return status;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineDefaultCreate(Nucleus_Media_Plugin_Direct3D_VideoSystemWindow)
