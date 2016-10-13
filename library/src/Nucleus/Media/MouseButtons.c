/// @file Nucleus/Media/MouseButtons.c
/// @brief Mouse buttons.
#include "Nucleus/Media/MouseButtons.h"

#include <stdio.h>

Nucleus_NonNull(2) int
Nucleus_MouseButtons_toString
    (
        Nucleus_MouseButtons button,
        const char **string
    )
{
    if (!string)
    {
        return 1;
    }
    switch (button)
    {
    #define Alias(aliased,alias)
    #define Define(name,value,description)\
        case Nucleus_MouseButtons_##name:\
        {\
            static const char *STRING = description;\
            *string = STRING;\
            return 0;\
        };
    #include "Nucleus/Media/MouseButtons.in"
    #undef Define
    #undef Alias
        default:
        {
            fprintf(stderr, "%s:%d: unknown mouse button %d\n", __FILE__, __LINE__, button);
            return 1;
        };
    };
}
