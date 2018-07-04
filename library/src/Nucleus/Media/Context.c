// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Media/Context-private.c.i"

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_get
   (
      Nucleus_MediaContext **mediaContext
   )
{
   if (Nucleus_Unlikely(!mediaContext))
   { return Nucleus_Status_InvalidArgument; }
   // lock
   if (Nucleus_Unlikely(!g_singleton))
   {
       // unlock
       return Nucleus_Status_NotExists;
   }
   *mediaContext = g_singleton;
   // unlock
   return Nucleus_Status_Success;
}

Nucleus_Status
Nucleus_MediaContext_initialize
    (
    )
{
    if (NULL != g_singleton)
    {
        return Nucleus_Status_Exists;
    }
    return create(&g_singleton);
}

Nucleus_Status
Nucleus_MediaContext_uninitialize
    (
    )
{
    if (NULL == g_singleton)
    {
        return Nucleus_Status_NotExists;
    }
    Nucleus_MediaContext_shutdown(g_singleton);
    destroy(g_singleton);
    g_singleton = NULL;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_registerAudioSystemFactory
    (
        Nucleus_MediaContext *context,
        Nucleus_Media_AudioSystemFactory *audioSystemFactory
    )
{
    if (Nucleus_Unlikely(!context || !audioSystemFactory)) return Nucleus_Status_InvalidArgument;
    return Nucleus_ObjectArray_append(context->audioSystemFactories, NUCLEUS_OBJECT(audioSystemFactory));
}

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_getAudioSystemFactories
    (
        Nucleus_MediaContext *mediaContext,
        Nucleus_ObjectEnumerator **enumerator
    )
{
    if (Nucleus_Unlikely(!mediaContext || !enumerator)) return Nucleus_Status_InvalidArgument;
    return Nucleus_ObjectArray_getEnumerator(mediaContext->audioSystemFactories, enumerator);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_registerVideoSystemFactory
    (
        Nucleus_MediaContext *context,
        Nucleus_Media_VideoSystemFactory *videoSystemFactory
    )
{
    if (Nucleus_Unlikely(!context || !videoSystemFactory)) return Nucleus_Status_InvalidArgument;
    return Nucleus_ObjectArray_append(context->videoSystemFactories, NUCLEUS_OBJECT(videoSystemFactory));
}

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_getVideoSystemFactories
    (
        Nucleus_MediaContext *mediaContext,
        Nucleus_ObjectEnumerator **enumerator  
    )
{
    if (Nucleus_Unlikely(!mediaContext || !enumerator)) return Nucleus_Status_InvalidArgument;
    return Nucleus_ObjectArray_getEnumerator(mediaContext->videoSystemFactories, enumerator);
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_MediaContext_startup
    (
        Nucleus_MediaContext *context,
        Nucleus_Status(*selectVideoSystemFactory)(Nucleus_Media_VideoSystemFactory **factory),
        Nucleus_Status(*selectVideoSystemConfiguration)(Nucleus_ObjectEnumerator *enumerator,
                                                        Nucleus_Media_VideoSystemConfiguration **configuration),
        Nucleus_Status(*selectAudioSystemFactory)(Nucleus_Media_AudioSystemFactory **factory),
        Nucleus_Status(*selectAudioSystemConfiguration)(Nucleus_ObjectEnumerator *enumerator,
                                                        Nucleus_Media_AudioSystemConfiguration **configuration)
    )
{
    Nucleus_Status status;
    //
    status = Nucleus_MediaContext_loadPluginLibraries(context);
    if (Nucleus_Unlikely(status)) return status;
    //
    status = Nucleus_MediaContext_registerPlugins(context);
    if (Nucleus_Unlikely(status)) return status;
    //
    status = Nucleus_MediaContext_startupPlugins(context);
    if (Nucleus_Unlikely(status)) return status;
    //
    if (!selectVideoSystemFactory)
    {
        fprintf(stderr, "ERROR: no video system selection function provided\n");
        return Nucleus_Status_InvalidArgument;
    }
    {
        Nucleus_Media_VideoSystemFactory *factory;
        status = selectVideoSystemFactory(&factory);
        if (Nucleus_Unlikely(status))
        {
            return status;
        }
        if (!factory)
        {
            fprintf(stderr, "no video system factory selected\n");
            return Nucleus_Status_InvalidArgument;
        }
        if (!selectVideoSystemConfiguration)
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
            fprintf(stderr, "ERROR: no video system configuration selection function provided\n");
            return Nucleus_Status_InvalidArgument;
        }
        //
        Nucleus_ObjectArray *configurations;
        status = Nucleus_Media_VideoSystemFactory_getConfigurations(factory, &configurations);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
            return status;
        }
        //
        Nucleus_ObjectEnumerator *enumerator;
        status = Nucleus_ObjectArray_getEnumerator(configurations, &enumerator);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configurations));
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
            return status;
        }
        //
        Nucleus_Media_VideoSystemConfiguration *configuration;
        status = (*selectVideoSystemConfiguration)(enumerator, &configuration);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(enumerator));
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configurations));
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
            return status;
        }
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configurations));
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(enumerator));
        //
        if (!configuration)
        {
            fprintf(stderr, "ERROR: no video system configuration provided\n");
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
            return Nucleus_Status_InvalidArgument;
        }
        //
        status = Nucleus_Media_VideoSystemFactory_createSystem(factory, &context->videoSystem);
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configuration));
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
        if (Nucleus_Unlikely(status)) return status;
    }
    //
    if (!selectAudioSystemFactory)
    {
        fprintf(stderr, "ERROR: no audio system selection function provided\n");
        return Nucleus_Status_InvalidArgument;
    }
    {
        Nucleus_Media_AudioSystemFactory *factory;
        status = selectAudioSystemFactory(&factory);
        if (Nucleus_Unlikely(status))
        {
            return status;
        }
        if (!factory)
        {
            fprintf(stderr, "no audio system factory selected\n");
            return Nucleus_Status_InvalidArgument;
        }
        if (!selectAudioSystemConfiguration)
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
            fprintf(stderr, "ERROR: no audio system confiuration selection function provided\n");
            return Nucleus_Status_InvalidArgument;
        }
        //
        Nucleus_ObjectArray *configurations;
        status = Nucleus_Media_AudioSystemFactory_getConfigurations(factory, &configurations);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
            return status;
        }
        //
        Nucleus_ObjectEnumerator *enumerator;
        status = Nucleus_ObjectArray_getEnumerator(configurations, &enumerator);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configurations));
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
            return status;
        }
        //
        Nucleus_Media_AudioSystemConfiguration *configuration;
        status = (*selectAudioSystemConfiguration)(enumerator, &configuration);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(enumerator));
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configurations));
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
            return status;
        }
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configurations));
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(enumerator));
        //
        if (!configuration)
        {
            fprintf(stderr, "ERROR: no audio system configuration provided\n");
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
            return Nucleus_Status_InvalidArgument;
        }
        //
        status = Nucleus_Media_AudioSystemFactory_createSystem(factory, &context->audioSystem);
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configuration));
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(factory));
        if (status) return status;
    }
    return status;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_shutdown
    (
        Nucleus_MediaContext *context
    )
{
    if (context->audioSystem)
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context->audioSystem));
        context->audioSystem = NULL;
    }
    if (context->videoSystem)
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(context->videoSystem));
        context->videoSystem = NULL;
    }
    //
    Nucleus_MediaContext_shutdownPlugins(context);
    //
    Nucleus_MediaContext_unregisterPlugins(context);
    //
    return Nucleus_Status_Success;
}
