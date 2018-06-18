// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Media/Context.h"
#include "Nucleus/Media/ApplicationEvent.h"
#include "Nucleus/Media/MouseButtonEvent.h"
#include "Nucleus/Media/MousePointerEvent.h"
#include "Nucleus/Media/KeyboardKeyEvent.h"
#include <stdlib.h>

Nucleus_Status
testApplicationEvent
    (
    )
{
    Nucleus_ApplicationEvent *event;
    //
    Nucleus_ApplicationEvent_create(&event, Nucleus_ApplicationEventKinds_Closed);
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(event));
    //
    return Nucleus_Status_Success;
}
    
Nucleus_Status
testMouseButtonEvent
    (
    )
{
    Nucleus_MouseButtonEvent *event;
    //
    Nucleus_MouseButtonEvent_create(&event, Nucleus_MouseButtonEventKinds_Pressed,
                                    Nucleus_MouseButtons_Button0, 0, 0, 0);
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(event));
    //
    Nucleus_MouseButtonEvent_create(&event, Nucleus_MouseButtonEventKinds_Released,
                                    Nucleus_MouseButtons_Button0, 0, 0, 0);
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(event));
    //
    return Nucleus_Status_Success;
}

Nucleus_Status
testMousePointerEvent
    (
    )
{
    Nucleus_MousePointerEvent *event;
    //
    Nucleus_MousePointerEvent_create(&event, Nucleus_MousePointerEventKinds_Move,
                                     0, 0, 0);
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(event));
    //
    Nucleus_MousePointerEvent_create(&event, Nucleus_MousePointerEventKinds_Enter,
                                     0, 0, 0);
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(event));
    //
    Nucleus_MousePointerEvent_create(&event, Nucleus_MousePointerEventKinds_Leave,
                                     0, 0, 0);
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(event));
    //
    return Nucleus_Status_Success;
}


Nucleus_Status
testKeyboardKeyEvent
    (
    )
{
    Nucleus_KeyboardKeyEvent *event;
    //
    Nucleus_KeyboardKeyEvent_create(&event, Nucleus_KeyboardKeyEventKinds_Pressed,
                                    Nucleus_KeyboardKeys_Escape, 0);
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(event));
    //
    Nucleus_KeyboardKeyEvent_create(&event, Nucleus_KeyboardKeyEventKinds_Released,
                                    Nucleus_KeyboardKeys_Escape, 0);
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(event));
    //
    return Nucleus_Status_Success; 
}

int
main
    (
        int argc,
        char **argv
    )
{
    int exitCode = EXIT_SUCCESS;
    Nucleus_Status status;
    
    status = Nucleus_Types_initialize();
    if (Nucleus_Unlikely(status)) { return EXIT_FAILURE; }

    status = testApplicationEvent();
    if (Nucleus_Unlikely(status)) { exitCode = EXIT_FAILURE; goto End; }

    status = testKeyboardKeyEvent();
    if (Nucleus_Unlikely(status)) { exitCode = EXIT_FAILURE; goto End; }

    status = testMouseButtonEvent();
    if (Nucleus_Unlikely(status)) { exitCode = EXIT_FAILURE; goto End; }

    status = testMousePointerEvent();
    if (Nucleus_Unlikely(status)) { exitCode = EXIT_FAILURE; goto End; }

End:
    Nucleus_Types_uninitialize();
    return exitCode;
}
