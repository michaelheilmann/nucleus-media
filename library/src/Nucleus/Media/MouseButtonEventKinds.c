/// @file Nucleus/Media/MouseButtonEventKinds.c
/// @brief Kinds of mouse button events.
#include "Nucleus/Media/MouseButtonEventKinds.h"

#include <stdio.h>

Nucleus_NonNull(2) Nucleus_Status
Nucleus_MouseButtonEventKinds_toString
    (
        Nucleus_MouseButtonEventKinds kind,
        const char **string
    )
{
    if (Nucleus_Unlikely(!string)) return Nucleus_Status_InvalidArgument;
    switch (kind)
    {
    #define Alias(aliased,alias)
    #define Define(name,value,description)\
        case Nucleus_MouseButtonEventKinds_##name:\
        {\
            static const char *STRING = description;\
            *string = STRING;\
            return Nucleus_Status_Success;\
        };
    #include "Nucleus/Media/MouseButtonEventKinds.in"
    #undef Define
    #undef Alias
        default:
        {
            fprintf(stderr, "%s:%d: unknown mouse button event kind %d\n", __FILE__, __LINE__, kind);
            return Nucleus_Status_InternalError;
        };
    };
}
