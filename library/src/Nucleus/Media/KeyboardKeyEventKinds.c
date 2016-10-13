/// @file Nucleus/Media/KeyboardKeyEventKinds.c
/// @brief Kinds of keyboard key events.
#include "Nucleus/Media/KeyboardKeyEventKinds.h"

#include <stdio.h>

Nucleus_NonNull(2) Nucleus_Status
Nucleus_KeyboardKeyEventKinds_toString
    (
        Nucleus_KeyboardKeyEventKinds kind,
        const char **string
    )
{
    if (Nucleus_Unlikely(!string)) return Nucleus_Status_InvalidArgument;
    switch (kind)
    {
    #define Alias(aliased,alias)
    #define Define(name,value,description)\
        case Nucleus_KeyboardKeyEventKinds_##name:\
        {\
            static const char *STRING = description;\
            *string = STRING;\
            return 0;\
        };
    #include "Nucleus/Media/KeyboardKeyEventKinds.in"
    #undef Define
    #undef Alias
        default:
        {
            fprintf(stderr, "%s:%d: unknown mouse button event kind %d\n", __FILE__, __LINE__, kind);
            return Nucleus_Status_InternalError;
        };
    };
}
