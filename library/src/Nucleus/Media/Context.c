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
    destroy(g_singleton);
    g_singleton = NULL;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_registerAudioSystemFactory
    (
        Nucleus_MediaContext *mediaContext,
        Nucleus_AudioSystemFactory *audioSystemFactory
    )
{
    if (Nucleus_Unlikely(!mediaContext || !audioSystemFactory)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_registerVideoSystemFactory
    (
        Nucleus_MediaContext *mediaContext,
        Nucleus_VideoSystemFactory *videoSystemFactory
    )
{
    if (Nucleus_Unlikely(!mediaContext || !videoSystemFactory)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_startup
    (
        Nucleus_MediaContext *context,
        Nucleus_Status(*selectVideoSystemFactory)(Nucleus_VideoSystemFactory **factory),
        Nucleus_Status(*selectAudioSystemFactory)(Nucleus_AudioSystemFactory **factory)
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
    return status;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_shutdown
    (
        Nucleus_MediaContext *context
    )
{
    //
    Nucleus_MediaContext_shutdownPlugins(context);
    //
    Nucleus_MediaContext_unregisterPlugins(context);
    //
    Nucleus_MediaContext_unloadPluginLibraries(context);
    //
    return Nucleus_Status_Success;
}
