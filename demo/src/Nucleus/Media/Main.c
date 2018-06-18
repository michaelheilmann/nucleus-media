// Copyright (c) 2018 Michael Heilmann
#include <stdlib.h>
#include "Nucleus/Media/Context.h"

Nucleus_NonNull() static Nucleus_Status
selectVideoSystemFactory
    (
        Nucleus_Media_VideoSystemFactory **factory
    )
{
    Nucleus_MediaContext *context;
    Nucleus_Status status;
    // Validate arguments.
    if (Nucleus_Unlikely(!factory)) return Nucleus_Status_InvalidArgument;
    // Get the media context.
    status = Nucleus_MediaContext_get(&context);
    if (Nucleus_Unlikely(status)) return status;
    // Get the enumerator of the video system factories.
    Nucleus_ObjectEnumerator *e;
    status = Nucleus_MediaContext_getVideoSystemFactories(context, &e);
    if (Nucleus_Unlikely(status)) return status;
    Nucleus_Media_VideoSystemFactory *best = NULL;
    while (Nucleus_Boolean_True)
    {
        Nucleus_Boolean hasObject;
        status = Nucleus_ObjectEnumerator_hasObject(e, &hasObject);
        if (Nucleus_Unlikely(status))
        {
            if (best)
            {
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            }
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(e));
            return status;
        }
        if (!hasObject)
        {
            break;
        }
        Nucleus_Media_VideoSystemFactory *current;
        status = Nucleus_ObjectEnumerator_getObject(e, (Nucleus_Object **)&current);
        if (Nucleus_Unlikely(status))
        {
            if (best)
            {
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            }
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(e));
            return status;
        }
        // Must simplistic choice: Use the first one.
        if (NULL == best)
        {
            best = current;
        }
        else
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(current));
        }
        //
        status = Nucleus_ObjectEnumerator_nextObject(e);
        if (Nucleus_Unlikely(status))
        {
            if (best)
            {
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            }
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(e));
            return status;
        }
    }
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(e));
    *factory = best;
    // Return with success.
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
selectAudioSystemFactory
    (
        Nucleus_Media_AudioSystemFactory **factory
    )
{
    Nucleus_MediaContext *context;
    Nucleus_Status status;
    // Validate arguments.
    if (Nucleus_Unlikely(!factory)) return Nucleus_Status_InvalidArgument;
    // Get the media context.
    status = Nucleus_MediaContext_get(&context);
    if (Nucleus_Unlikely(status)) return status;
    // Get the enumerator of the audio system factories.
    Nucleus_ObjectEnumerator *e;
    status = Nucleus_MediaContext_getAudioSystemFactories(context, &e);
    if (Nucleus_Unlikely(status)) return status;
    Nucleus_Media_AudioSystemFactory *best = NULL;
    while (Nucleus_Boolean_True)
    {
        Nucleus_Boolean hasObject;
        status = Nucleus_ObjectEnumerator_hasObject(e, &hasObject);
        if (Nucleus_Unlikely(status))
        {
            if (best)
            {
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            }
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(e));
            return status;
        }
        if (!hasObject)
        {
            break;
        }
        Nucleus_Media_AudioSystemFactory *current;
        status = Nucleus_ObjectEnumerator_getObject(e, (Nucleus_Object **)&current);
        if (Nucleus_Unlikely(status))
        {
            if (best)
            {
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            }
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(e));
            return status;
        }
        // Must simplistic choice: Use the first one.
        if (NULL == best)
        {
            best = current;
        }
        else
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(current));
        }
        //
        status = Nucleus_ObjectEnumerator_nextObject(e);
        if (Nucleus_Unlikely(status))
        {
            if (best)
            {
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            }
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(e));
            return status;
        }
    }
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(e));
    *factory = best;
    // Return with success.
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

    status = Nucleus_MediaContext_initialize();
    if (Nucleus_Unlikely(status)) { return EXIT_FAILURE; }

    Nucleus_MediaContext *mediaContext;
    status = Nucleus_MediaContext_get(&mediaContext);
    if (Nucleus_Unlikely(status)) { exitCode = EXIT_FAILURE; goto End; }

    status = Nucleus_MediaContext_startup(mediaContext, &selectVideoSystemFactory,
                                                        &selectAudioSystemFactory);
    if (Nucleus_Unlikely(status)) { exitCode = EXIT_FAILURE; goto End; }

    status = Nucleus_MediaContext_shutdown(mediaContext);
    if (Nucleus_Unlikely(status)) { exitCode = EXIT_FAILURE; goto End; }

End:
    Nucleus_MediaContext_uninitialize();
    return exitCode;
}
