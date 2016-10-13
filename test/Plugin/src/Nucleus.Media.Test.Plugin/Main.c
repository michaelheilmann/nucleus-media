// Copyright (c) 2018 Michael Heilmann
#include <stdlib.h>
#include "Nucleus/Media/Context.h"

#if 0
Nucleus_NonNull() static Nucleus_Status
selectVideoSystemFactory
    (
        Nucleus_VideoSystemFactory **factory
    )
{
    Nucleus_MediaContext *context;
    Nucleus_Status status;
    // Validate arguments.
    if (Nucleus_Unlikely(!factory)) return Nucleus_Status_InvalidArgument;
    // Get the media context.
    status = Nucleus_MediaContext_get(&context);
    if (Nucleus_Unlikely(status)) return status;
    // Return with success.
    return Nucleus_Status_Success;
}
#endif

#if 0
Nucleus_NonNull() static Nucleus_Status
selectAudioSystemFactory
    (
        Nucleus_AudioSystemFactory **factory
    )
{
    Nucleus_MediaContext *context;
    Nucleus_Status status;
    // Validate arguments.
    if (Nucleus_Unlikely(!factory)) return Nucleus_Status_InvalidArgument;
    // Get the media context.
    status = Nucleus_MediaContext_get(&context);
    if (Nucleus_Unlikely(status)) return status;
    // Return with success.
    return Nucleus_Status_Success;
}
#endif

int
main
    (
        int argc,
        char **argv
    )
{
    int exitCode = EXIT_SUCCESS;
    Nucleus_Status status;
    //
    status = Nucleus_MediaContext_initialize();
    if (Nucleus_Unlikely(status)) { return EXIT_FAILURE; }
    //
    Nucleus_MediaContext *context;
    status = Nucleus_MediaContext_get(&context);
    if (Nucleus_Unlikely(status)) { exitCode = EXIT_FAILURE; goto End; }
    //
    status = Nucleus_MediaContext_startup(context, NULL, NULL);
    if (Nucleus_Unlikely(status))
    { exitCode = EXIT_FAILURE; goto End; }
    //
    status = Nucleus_MediaContext_shutdown(context);
    if (Nucleus_Unlikely(status))
    { exitCode = EXIT_FAILURE; goto End; }
    //
End:
    Nucleus_MediaContext_uninitialize();
    return exitCode;
}
