// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.OpenGL/GLX/GLX_ARB_create_context.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)

#include "Nucleus.Media.Plugin.OpenGL/isExtensionSupported.h"
#include <stdio.h>

GLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = NULL;

Nucleus_Status initialize_GLX_ARB_create_context(Display *dpy)
{
    const char *extensions = glXQueryExtensionsString(dpy, DefaultScreen(dpy));
	if (NULL == extensions)
	{
		fprintf(stderr, "[GLX Extension Library, %s, %d] %s failed\n", __FILE__, __LINE__, "glXQueryExtensionsString");
		return Nucleus_Status_EnvironmentFailed;
	}
	Nucleus_Status status;
	Nucleus_Boolean isSupported;
	status = isExtensionSupported(extensions, "GLX_ARB_create_context_profile", &isSupported);
	if (Nucleus_Unlikely(status)) return status;
	if (!isSupported)
	{
		fprintf(stderr, "[GLX Extension Library, %s, %d] extension %s is not supported\n", __FILE__, __LINE__, "GLX_ARB_create_context_profile");
		fprintf(stderr, "extension string is %s\n", extensions);
		return Nucleus_Status_EnvironmentFailed;
	}
    glXCreateContextAttribsARB = (GLXCREATECONTEXTATTRIBSARBPROC)
                                 glXGetProcAddress((const GLubyte *)"glXCreateContextAttribsARB");
	if (!glXCreateContextAttribsARB)
	{
		fprintf(stderr, "[GLX Extension Library, %s, %d] %s is not supported\n", __FILE__, __LINE__, "GLX_ARB_create_context_profile");
		return Nucleus_Status_EnvironmentFailed;		
	}
	return Nucleus_Status_Success;
}

#endif
