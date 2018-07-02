// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Media/VideoSystem.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            "Nucleus.Media.VideoSystem",
                            Nucleus_Media_VideoSystem,
                            Nucleus_Object)

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_VideoSystem_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_VideoSystem_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_VideoSystem *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystem_construct
    (
        Nucleus_Media_VideoSystem *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_VideoSystem_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Object_construct(NUCLEUS_OBJECT(self));
    if (Nucleus_Unlikely(status)) return status;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystem_createWindow
    (
        Nucleus_Media_VideoSystem *self,
		Nucleus_Media_VideoSystemWindow **window
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
	return getDispatch(self)->createWindow(self, window);
}
