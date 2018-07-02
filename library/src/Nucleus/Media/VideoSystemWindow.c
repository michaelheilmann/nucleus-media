#include "Nucleus/Media/VideoSystemWindow.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            u8"Nucleus.Media.VideoSystemWindow",
                            Nucleus_Media_VideoSystemWindow,
                            Nucleus_Object)

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_VideoSystemWindow_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_VideoSystemWindow_Class *dispatch
    )
{
	Nucleus_Type *type = NUCLEUS_OBJECT_CLASS(dispatch)->type;
	Nucleus_Status status;
	status = Nucleus_Signals_addSignal(u8"keyboard-key-pressed", type);
	if (Nucleus_Unlikely(status)) return status;
	status = Nucleus_Signals_addSignal(u8"keyboard-key-released", type);
	if (Nucleus_Unlikely(status)) return status;
	status = Nucleus_Signals_addSignal(u8"mouse-pointer-moved", type);
	if (Nucleus_Unlikely(status)) return status;
	status = Nucleus_Signals_addSignal(u8"mouse-button-pressed", type);
	if (Nucleus_Unlikely(status)) return status;
	status = Nucleus_Signals_addSignal(u8"mouse-button-released", type);
	if (Nucleus_Unlikely(status)) return status;
	status = Nucleus_Signals_addSignal(u8"window-closing", type);
	if (Nucleus_Unlikely(status)) return status;
	status = Nucleus_Signals_addSignal(u8"window-closed", type);
	if (Nucleus_Unlikely(status)) return status;
	return Nucleus_Status_Success;
}

Nucleus_AlwaysSucceed() Nucleus_NonNull(1) static Nucleus_Status
destruct
    (
        Nucleus_Media_VideoSystemWindow *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemWindow_construct
    (
        Nucleus_Media_VideoSystemWindow *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_VideoSystemWindow_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Media_VideoSystemWindow_construct(NUCLEUS_MEDIA_VIDEOSYSTEMWINDOW(self));
    if (Nucleus_Unlikely(status)) return status;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}
