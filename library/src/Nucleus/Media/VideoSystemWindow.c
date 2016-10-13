#include "Nucleus/Media/VideoSystemWindow.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            "Nucleus.Media.VideoSystemWindow",
                            Nucleus_Media_VideoSystemWindow,
                            Nucleus_Object)

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_VideoSystemWindow_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull(1) static Nucleus_Status
destruct
    (
        Nucleus_Media_VideoSystemWindow *self
    )
{ return Nucleus_Status_Success; }


Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemWindow_construct
    (
        Nucleus_Media_VideoSystemWindow *self
    );
