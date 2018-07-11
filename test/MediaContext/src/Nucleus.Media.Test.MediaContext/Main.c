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
    status = Nucleus_Objects_initialize();
    if (Nucleus_Unlikely(status))
    {
        return EXIT_FAILURE;
    }
    Nucleus_Media_Context *context;
    status = Nucleus_Media_Context_create(&context);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Objects_uninitialize();
        return EXIT_FAILURE;
    }
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
    Nucleus_Objects_uninitialize();
    return EXIT_SUCCESS;
}
