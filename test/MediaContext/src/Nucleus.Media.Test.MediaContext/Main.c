// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Media/Context.h"
#include <stdlib.h>

int
main
    (
        int argc,
        char **argv
    )
{
    Nucleus_Status status;
    
    status = Nucleus_MediaContext_initialize();
    if (Nucleus_Unlikely(status)) { return EXIT_FAILURE; }
    
    Nucleus_MediaContext_uninitialize();
    
    return EXIT_SUCCESS;
}
