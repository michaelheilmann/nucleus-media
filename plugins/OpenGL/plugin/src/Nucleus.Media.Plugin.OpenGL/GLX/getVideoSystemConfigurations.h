#pragma once

#include "Nucleus/Object/ObjectArray.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) 

Nucleus_NonNull() Nucleus_Status
getVideoSystemConfigurations
    (
		Nucleus_ObjectArray *configurations
    );

#endif
