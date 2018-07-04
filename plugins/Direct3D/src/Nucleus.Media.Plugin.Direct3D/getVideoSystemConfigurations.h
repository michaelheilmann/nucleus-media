#pragma once

#include "Nucleus/Object/ObjectArray.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

Nucleus_NonNull() Nucleus_Status
getVideoSystemConfigurations
    (
        Nucleus_ObjectArray *configurations
    );

#endif
