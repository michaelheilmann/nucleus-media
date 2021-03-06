// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Object/ObjectArray.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) 

Nucleus_NonNull() Nucleus_Status
getAudioSystemConfigurations
    (
		Nucleus_ObjectArray *configurations
    );
    
#endif
