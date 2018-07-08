#include "Nucleus.Media.Plugin.Direct3D/getVideoSystemConfigurations.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus/Media/VideoSystemConfiguration.h"

Nucleus_NonNull() Nucleus_Status
getVideoSystemConfigurations
    (
        Nucleus_ObjectArray *configurations
    )
{
    if (Nucleus_Unlikely(!configurations)) return Nucleus_Status_InvalidArgument;
    //
    Nucleus_Status status;
    Nucleus_Media_VideoSystemConfiguration *configuration;
    //
    status = Nucleus_Media_VideoSystemConfiguration_create(&configuration);
    if (Nucleus_Unlikely(status))
    {
        return status;
    }
    //
    status = Nucleus_ObjectArray_append(configurations, NUCLEUS_OBJECT(configuration));
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configuration));
    if (Nucleus_Unlikely(status))
    {
        return status;
    }
    //
    return Nucleus_Status_Success;
}

#endif
