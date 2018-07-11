// Copyright (c) 2018 Michael Heilmann
#include <stdlib.h>
#include "Nucleus/Media/Context.h"

Nucleus_NonNull() static Nucleus_Status
selectVideoSystemConfiguration
    (
        Nucleus_ObjectEnumerator *enumerator,
        Nucleus_Media_VideoSystemConfiguration **configuration
    )
{
    if (Nucleus_Unlikely(!enumerator || !configuration)) return Nucleus_Status_InvalidArgument;
    Nucleus_Media_VideoSystemConfiguration *best = NULL;
    while (Nucleus_Boolean_True)
    {
        Nucleus_Status status;
        Nucleus_Boolean hasObject;
        status = Nucleus_ObjectEnumerator_hasObject(enumerator, &hasObject);
        if (Nucleus_Unlikely(status))
        {
            if (best) Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            return status;
        }
        if (!hasObject)
        {
            break;
        }
        Nucleus_Media_VideoSystemConfiguration *current;
        status = Nucleus_ObjectEnumerator_getObject(enumerator, (Nucleus_Object **)&current);
        if (Nucleus_Unlikely(status))
        {
            if (best) Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            return status;
        }
        if (!best)
        {
            best = current;
        }
        else
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(current));
        }
        status = Nucleus_ObjectEnumerator_nextObject(enumerator);
        if (Nucleus_Unlikely(status))
        {
            if (best) Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            return status;          
        }
    }
    *configuration = best;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
selectVideoSystemFactory
    (
        Nucleus_Media_VideoSystemFactory **factory
    )
{
    Nucleus_Media_Context *context;
    Nucleus_Status status;
    // Validate arguments.
    if (Nucleus_Unlikely(!factory)) return Nucleus_Status_InvalidArgument;
    // Get the media context.
    status = Nucleus_Media_Context_create(&context);
    if (Nucleus_Unlikely(status)) return status;
    // Get the enumerator of the video system factories.
    Nucleus_ObjectEnumerator *e;
    status = Nucleus_Media_Context_getVideoSystemFactories(context, &e);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
        return status;
    }
    Nucleus_Media_VideoSystemFactory *best = NULL;
    while (Nucleus_Boolean_True)
    {
        Nucleus_Status status;
        Nucleus_Boolean hasObject;
        status = Nucleus_ObjectEnumerator_hasObject(e, &hasObject);
        if (Nucleus_Unlikely(status))
        {
            if (best)
            {
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            }
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(e));
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
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
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
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
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
            return status;
        }
    }
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(e));
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
    *factory = best;
    // Return with success.
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
selectAudioSystemConfiguration
    (
        Nucleus_ObjectEnumerator *enumerator,
        Nucleus_Media_AudioSystemConfiguration **configuration
    )
{
    if (Nucleus_Unlikely(!enumerator || !configuration)) return Nucleus_Status_InvalidArgument;
    Nucleus_Media_AudioSystemConfiguration *best = NULL;
    while (Nucleus_Boolean_True)
    {
        Nucleus_Status status;
        Nucleus_Boolean hasObject;
        status = Nucleus_ObjectEnumerator_hasObject(enumerator, &hasObject);
        if (Nucleus_Unlikely(status))
        {
            if (best) Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            return status;
        }
        if (!hasObject)
        {
            break;
        }
        Nucleus_Media_AudioSystemConfiguration *current;
        status = Nucleus_ObjectEnumerator_getObject(enumerator, (Nucleus_Object **)&current);
        if (Nucleus_Unlikely(status))
        {
            if (best) Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            return status;
        }
        if (!best)
        {
            best = current;
        }
        else
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(current));
        }
        status = Nucleus_ObjectEnumerator_nextObject(enumerator);
        if (Nucleus_Unlikely(status))
        {
            if (best) Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(best));
            return status;          
        }
    }
    *configuration = best;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
selectAudioSystemFactory
    (
        Nucleus_Media_AudioSystemFactory **factory
    )
{
    Nucleus_Media_Context *context;
    Nucleus_Status status;
    // Validate arguments.
    if (Nucleus_Unlikely(!factory)) return Nucleus_Status_InvalidArgument;
    // Get the media context.
    status = Nucleus_Media_Context_create(&context);
    if (Nucleus_Unlikely(status)) return status;
    // Get the enumerator of the audio system factories.
    Nucleus_ObjectEnumerator *e;
    status = Nucleus_Media_Context_getAudioSystemFactories(context, &e);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
        return status;
    }
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
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
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
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
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
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
            return status;
        }
    }
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(e));
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
    *factory = best;
    // Return with success.
    return Nucleus_Status_Success;
}

static Nucleus_Status
mediaMain
    (
        int argc,
        char **argv
    )
{
    Nucleus_Status status;
    //
    Nucleus_Media_Context *context;
    status = Nucleus_Media_Context_create(&context);
    if (Nucleus_Unlikely(status))
    { return status; }
    //
    status = Nucleus_Media_Context_startup(context, &selectVideoSystemFactory,
                                                    &selectVideoSystemConfiguration,
                                                    &selectAudioSystemFactory,
                                                    &selectAudioSystemConfiguration);
    if (Nucleus_Unlikely(status))
    { 
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
        return status;
    }
    //
    Nucleus_Media_VideoSystem *videoSystem;
    status = Nucleus_Media_Context_getVideoSystem(context, &videoSystem);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
        return status;
    }
    //
    Nucleus_Media_AudioSystem *audioSystem;
    status = Nucleus_Media_Context_getAudioSystem(context, &audioSystem);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(videoSystem));
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context));
        return status;
    }
    //
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(audioSystem));
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(videoSystem));
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context)); // Implicit Nucleus_Media_Context_uninitialize().
    //
    return status;
}

int
main
    (
        int argc,
        char **argv
    )
{
    Nucleus_Status status;
    //
    status = Nucleus_Objects_initialize();
    if (Nucleus_Unlikely(status))
    {
        return EXIT_FAILURE;
    }
    //
    status = mediaMain(argc, argv);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Objects_uninitialize();
        return EXIT_FAILURE;
    }
    //
    Nucleus_Objects_uninitialize();
    //
    return EXIT_SUCCESS;
}
