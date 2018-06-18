// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.XAudio2/Plugin.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    #define Nucleus_PluginExport() __declspec(dllexport)
#else
    #define Nucleus_PluginExport()
#endif

Nucleus_PluginExport() Nucleus_Status
createPlugin
    (
        Nucleus_Media_Plugin **plugin
    )
{
    Nucleus_Media_Plugin_XAudio2_Plugin *temporary;
    Nucleus_Status status;
    if (Nucleus_Unlikely(!plugin)) return Nucleus_Status_InvalidArgument;
    status = Nucleus_Media_Plugin_XAudio2_Plugin_create(&temporary);
    if (Nucleus_Unlikely(status)) return status;
    *plugin = NUCLEUS_MEDIA_PLUGIN(temporary);
    return Nucleus_Status_Success;
}
