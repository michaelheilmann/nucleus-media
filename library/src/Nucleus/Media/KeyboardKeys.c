/// @file Nucleus/Media/KeyboardKeys.c
/// @brief Keyboard keys.
#include "Nucleus/Media/KeyboardKeys.h"

#include <stdio.h>

Nucleus_NonNull(2) Nucleus_Status
Nucleus_KeyboardKeys_toString
    (
        Nucleus_KeyboardKeys key,
        const char **string
    )
{
    if (Nucleus_Unlikely(!string)) return Nucleus_Status_InvalidArgument;
    switch (key)
    {
    #define Alias(aliased,alias)
    #define Define(name,value,description)\
        case Nucleus_KeyboardKeys_##name:\
        {\
            static const char *STRING = description;\
            *string = STRING;\
            return 0;\
        };
    #include "Nucleus/Media/KeyboardKeys.in"
    #undef Define
    #undef Alias
        default:
        {
            fprintf(stderr, "%s:%d: unknown keyboard key %d\n", __FILE__, __LINE__, key);
            return Nucleus_Status_InternalError;
        };
    };
}
