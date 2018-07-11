// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.OpenGL/WGL/WGL_ARB_create_context.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus.Media.Plugin.OpenGL/isExtensionSupported.h"
#include <gl/GL.h>

WGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

Nucleus_Status initialize_WGL_ARB_create_context()
{
    //
    wglCreateContextAttribsARB = (WGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    if (!wglCreateContextAttribsARB) return Nucleus_Status_EnvironmentFailed;
    //
    return Nucleus_Status_Success;
}

#endif
