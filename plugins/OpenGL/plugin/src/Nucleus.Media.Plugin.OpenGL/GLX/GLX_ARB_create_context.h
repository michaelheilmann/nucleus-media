// Copyright (c) 2018 Michael Heilmann
// https://www.khronos.org/registry/OpenGL/extensions/ARB/GLX_ARB_create_context.txt
#pragma once

#include "Nucleus/Configuration.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)
	
#include <X11/Xlib.h>
#include <GL/glx.h>

#include "Nucleus/Status.h"

#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
#define GLX_CONTEXT_FLAGS_ARB 0x2094
#define GLX_CONTEXT_PROFILE_MASK_ARB 0x9126
//#define GLX_CONTEXT_DEBUG_BIT_ARB 0x0001
//#define GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002
#define GLX_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

typedef GLXContext (*GLXCREATECONTEXTATTRIBSARBPROC)(Display *dpy,
                                                     GLXFBConfig config,
													 GLXContext context,
													 Bool share_context,
													 const int *attrib_list);
										
extern GLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;

Nucleus_Status initialize_GLX_ARB_create_context();

#endif
