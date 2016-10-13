/// @file Nucleus/Media/ApplicationEventKinds.c
/// @brief Kinds of application events.
#include "Nucleus/Media/ApplicationEventKinds.h"

#include <stdio.h>

Nucleus_NonNull(2) Nucleus_Status
Nucleus_ApplicationEventKinds_toString
    (
        Nucleus_ApplicationEventKinds kind,
        const char **string
    )
{
    if (Nucleus_Unlikely(!string)) return Nucleus_Status_InvalidArgument;
    switch (kind)
    {
    #define Alias(aliased,alias)
    #define Define(name,value,description)\
        case Nucleus_ApplicationEventKinds_##name:\
        {\
            static const char *STRING = description;\
            *string = STRING;\
            return Nucleus_Status_Success;\
        };
    #include "Nucleus/Media/ApplicationEventKinds.in"
    #undef Define
    #undef Alias
        default:
        {
            fprintf(stderr, "%s:%d: unknown application event kind %d\n", __FILE__, __LINE__, kind);
            return Nucleus_Status_InternalError;
        };
    };
}
