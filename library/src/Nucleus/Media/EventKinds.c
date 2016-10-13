/// @file Nucleus/Media/EventKinds.c
/// @brief Kinds of events.
#include "Nucleus/Media/EventKinds.h"

#include <stdio.h>

Nucleus_NonNull(2) Nucleus_Status
Nucleus_EventKinds_toString
    (
        Nucleus_EventKinds kind,
        const char **string
    )
{
    if (Nucleus_Unlikely(!string)) return Nucleus_Status_InvalidArgument;
    switch (kind)
    {
    #define Alias(aliased,alias)
    #define Define(name,value,description)\
        case Nucleus_EventKinds_##name:\
        {\
            static const char *STRING = description;\
            *string = STRING;\
            return Nucleus_Status_Success;\
        };
    #include "Nucleus/Media/EventKinds.in"
    #undef Define
    #undef Alias
        default:
        {
            fprintf(stderr, "%s:%d: unknown event kind %d\n", __FILE__, __LINE__, kind);
            return Nucleus_Status_InternalError;
        };
    };
}
