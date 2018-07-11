#include "Nucleus.Media.Plugin.OpenGL/isExtensionSupported.h"
#include <stdlib.h>
#include <string.h>

Nucleus_NonNull() Nucleus_Status
isExtensionSupported
    (
        const char *extensions,
        const char *extension,
        Nucleus_Boolean *isSupported
    )
{
    const char *start;
    const char *where, *terminator;

    // Extension name list must not be null.
    if (Nucleus_Unlikely(NULL == extension))
    { return Nucleus_Status_InvalidArgument; }
    // Extension names should not be null or empty.
    if (Nucleus_Unlikely(NULL == extension || *extension == '\0'))
    { return Nucleus_Status_InvalidArgument; }
    // Extension names should not have spaces.
    if (Nucleus_Unlikely(NULL != strchr(extension, ' ')))
    { return Nucleus_Status_InvalidArgument; }

    // Algorithm:
    // i denotes the iteration of the algorithm. The first iteration is 0.
    //
    // set start_i = extensions.
    // 
    // (*)
    // find the first occurence of extension in start_i
    // if there is no occurence,
    //   return that the extension is not supported.
    // start_i is of the form prefix extension suffix.
    // if prefix is empty or ends with a whitespace and suffix is empty or starts with a whitespace,
    //   return that the extension is supported.
    // set start_i+1 = suffix
    // Continue with iteration i + 1 at (*)
    for (start=extensions;;)
    {
        where = strstr(start, extension);
        if (!where)
        {
            *isSupported = Nucleus_Boolean_False;
            return Nucleus_Status_Success;
        }
        terminator = where + strlen(extension);
        if ((where == start || *(where - 1) == ' ') &&
            (*terminator == ' ' || *terminator == '\0'))
        {
            *isSupported = Nucleus_Boolean_True;
            return Nucleus_Status_Success;
        }
        start = terminator;
    }
    *isSupported = Nucleus_Boolean_False;
    return Nucleus_Status_Success;
}