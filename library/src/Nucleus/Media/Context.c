// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Media/Context-private.c.i"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            u8"Nucleus.Media.Context",
                            Nucleus_Media_Context,
                            Nucleus_Object)

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Context_Class *dispatch
    )
{
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Context_Class *dispatch
    )
{
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Context *self
    )
{
    //
    if (self->videoSystem)
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(self->videoSystem));
        self->videoSystem = NULL;
    }
    if (self->audioSystem)
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(self->audioSystem));
        self->audioSystem = NULL;
    }
    //
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(self->audioSystemFactories));
    self->audioSystemFactories = NULL;
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(self->videoSystemFactories));
    self->videoSystemFactories = NULL;
    //
    Nucleus_Collections_PointerHashMap_uninitialize(&self->plugins);
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_construct
    (
        Nucleus_Media_Context *self
    )
{
    if (Nucleus_Unlikely(!self))
    {
        return Nucleus_Status_InvalidArgument;
    }
    Nucleus_Status status;
    Nucleus_Type *type;
    status = Nucleus_Media_Context_getType(&type);
    if (Nucleus_Unlikely(status))
    {
        return status;
    }
    status = Nucleus_Object_construct(NUCLEUS_OBJECT(self));
    if (Nucleus_Unlikely(status))
    {
        return status;
    }
    // No video system or audio system selected.
    self->videoSystem = NULL;
    self->audioSystem = NULL;
    //
    status = Nucleus_Collections_PointerHashMap_initialize(&self->plugins,
                                                           0,
                                                           NUCLEUS_LOCKFUNCTION(&Nucleus_Object_incrementReferenceCount),
                                                           NUCLEUS_UNLOCKFUNCTION(&Nucleus_Object_decrementReferenceCount),
                                                           NUCLEUS_HASHFUNCTION(&Nucleus_Object_hash),
                                                           NUCLEUS_EQUALTOFUNCTION(&Nucleus_Object_equalTo),
                                                           NUCLEUS_LOCKFUNCTION(&Nucleus_Object_incrementReferenceCount),
                                                           NUCLEUS_UNLOCKFUNCTION(&Nucleus_Object_decrementReferenceCount));
    if (Nucleus_Unlikely(status))
    {
        return status;
    }
    //
    status = Nucleus_ObjectArray_create(&self->videoSystemFactories);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Collections_PointerHashMap_uninitialize(&self->plugins);
        return status;
    }
    //
    status = Nucleus_ObjectArray_create(&self->audioSystemFactories);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(self->videoSystemFactories));
        self->videoSystemFactories = NULL;
        Nucleus_Collections_PointerHashMap_uninitialize(&self->plugins);
        return status;
    }
    //
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DeclareSingletonCreate(Nucleus_Media_Context)

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_registerAudioSystemFactory
    (
        Nucleus_Media_Context *context,
        Nucleus_Media_AudioSystemFactory *audioSystemFactory
    )
{
    if (Nucleus_Unlikely(!context || !audioSystemFactory)) return Nucleus_Status_InvalidArgument;
    return Nucleus_ObjectArray_append(context->audioSystemFactories, NUCLEUS_OBJECT(audioSystemFactory));
}

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_getAudioSystemFactories
    (
        Nucleus_Media_Context *context,
        Nucleus_ObjectEnumerator **enumerator
    )
{
    if (Nucleus_Unlikely(!context || !enumerator)) return Nucleus_Status_InvalidArgument;
    return Nucleus_ObjectArray_getEnumerator(context->audioSystemFactories, enumerator);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_registerVideoSystemFactory
    (
        Nucleus_Media_Context *context,
        Nucleus_Media_VideoSystemFactory *videoSystemFactory
    )
{
    if (Nucleus_Unlikely(!context || !videoSystemFactory)) return Nucleus_Status_InvalidArgument;
    return Nucleus_ObjectArray_append(context->videoSystemFactories, NUCLEUS_OBJECT(videoSystemFactory));
}

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_getVideoSystemFactories
    (
        Nucleus_Media_Context *context,
        Nucleus_ObjectEnumerator **enumerator  
    )
{
    if (Nucleus_Unlikely(!context || !enumerator)) return Nucleus_Status_InvalidArgument;
    return Nucleus_ObjectArray_getEnumerator(context->videoSystemFactories, enumerator);
}

Nucleus_NonNull(1) Nucleus_Status
Nucleus_Media_Context_startup
    (
        Nucleus_Media_Context *context,
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
    status = Nucleus_Media_Context_loadPluginLibraries(context);
    if (Nucleus_Unlikely(status)) return status;
    //
    status = Nucleus_Media_Context_registerPlugins(context);
    if (Nucleus_Unlikely(status)) return status;
    //
    status = Nucleus_Media_Context_startupPlugins(context);
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
Nucleus_Media_Context_shutdown
    (
        Nucleus_Media_Context *context
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
    Nucleus_Media_Context_shutdownPlugins(context);
    //
    Nucleus_Media_Context_unregisterPlugins(context);
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_getVideoSystem
    (
        Nucleus_Media_Context *context,
        Nucleus_Media_VideoSystem **videoSystem
    )
{
    if (Nucleus_Unlikely(!context || !videoSystem)) return Nucleus_Status_InvalidArgument;
    Nucleus_Object_incrementReferenceCount(NUCLEUS_OBJECT(context->videoSystem));
    *videoSystem = context->videoSystem;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_getAudioSystem
    (
        Nucleus_Media_Context *context,
        Nucleus_Media_AudioSystem **audioSystem
    )
{
    if (Nucleus_Unlikely(!context || !audioSystem)) return Nucleus_Status_InvalidArgument;
    Nucleus_Object_incrementReferenceCount(NUCLEUS_OBJECT(context->audioSystem));
    *audioSystem = context->audioSystem;
    return Nucleus_Status_Success;
}

Nucleus_DefineSingletonCreate(Nucleus_Media_Context)
