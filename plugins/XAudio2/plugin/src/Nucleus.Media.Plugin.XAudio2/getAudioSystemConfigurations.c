// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.XAudio2/getAudioSystemConfigurations.h"

// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.XAudio2/getAudioSystemConfigurations.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
  
#include "Nucleus/Media/AudioSystemConfiguration.h"

Nucleus_NonNull() Nucleus_Status
getAudioSystemConfigurations
    (
        Nucleus_ObjectArray *configurations
    )
{
    if (Nucleus_Unlikely(!configurations)) return Nucleus_Status_InvalidArgument;
    //
    Nucleus_Status status;
    Nucleus_Media_AudioSystemConfiguration *configuration;
    //
    status = Nucleus_Media_AudioSystemConfiguration_create(&configuration);
    if (Nucleus_Unlikely(status))
    { return status; }
    //
    status = Nucleus_ObjectArray_append(configurations, NUCLEUS_OBJECT(configuration));
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configuration));
    if (Nucleus_Unlikely(status))
    { return status; }
    //
    return Nucleus_Status_Success;
}

#endif
