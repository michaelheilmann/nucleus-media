// Copyright (c) 2018 Michael Heilmann
/// @file Nucleus/Media/MousePointerEventKinds.c
/// @brief Kinds of mouse pointer events.
#include "Nucleus/Media/MousePointerEventKinds.h"

#include <stdio.h>

Nucleus_NonNull(2) Nucleus_Status
Nucleus_MousePointerEventKinds_toString
    (
        Nucleus_MousePointerEventKinds kind,
        const char **string
    )
{
    if (Nucleus_Unlikely(!string)) return Nucleus_Status_InvalidArgument;
    switch (kind)
    {
    #define Alias(aliased,alias)
    #define Define(name,value,description)\
        case Nucleus_MousePointerEventKinds_##name:\
        {\
            static const char *STRING = description;\
            *string = STRING;\
            return 0;\
        };
    #include "Nucleus/Media/MousePointerEventKinds.in"
    #undef Define
    #undef Alias
        default:
        {
            fprintf(stderr, "%s:%d: unknown mouse button event kind %d\n", __FILE__, __LINE__, kind);
            return Nucleus_Status_InternalError;
        };
    };
}
