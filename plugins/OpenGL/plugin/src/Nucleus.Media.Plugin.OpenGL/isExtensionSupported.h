// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Boolean.h"

Nucleus_NonNull() Nucleus_Status
isExtensionSupported
    (
        const char *extensions,
        const char *extension,
        Nucleus_Boolean *isSupported
    );
