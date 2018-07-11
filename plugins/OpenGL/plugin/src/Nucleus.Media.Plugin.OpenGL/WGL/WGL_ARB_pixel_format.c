// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.OpenGL/WGL/WGL_ARB_pixel_format.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#include "Nucleus.Media.Plugin.OpenGL/isExtensionSupported.h"
#include <gl/GL.h>

WGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB = NULL;

WGLGETPIXELFORMATATTRIBFVARBPROC wglGetPixelFormatAttribfvARB = NULL;

WGLCHOOSEPIXELFORMATARB wglChoosePixelFormatARB = NULL;

Nucleus_Status initialize_WGL_ARB_pixel_format()
{
    //
    wglGetPixelFormatAttribivARB = (WGLGETPIXELFORMATATTRIBIVARBPROC)wglGetProcAddress("wglGetPixelFormatAttribivARB");
    if (!wglGetPixelFormatAttribivARB) return Nucleus_Status_EnvironmentFailed;
    //
    wglGetPixelFormatAttribfvARB = (WGLGETPIXELFORMATATTRIBFVARBPROC)wglGetProcAddress("wglGetPixelFormatAttribfvARB");
    if (!wglGetPixelFormatAttribfvARB) return Nucleus_Status_EnvironmentFailed;
    //
    wglChoosePixelFormatARB = (WGLCHOOSEPIXELFORMATARB)wglGetProcAddress("wglChoosePixelFormatARB");
    if (!wglChoosePixelFormatARB) return Nucleus_Status_EnvironmentFailed;
    //
    return Nucleus_Status_Success;
}

#endif
