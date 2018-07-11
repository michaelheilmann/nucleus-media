// Copyright (c) 2018 Michael Heilmann
// https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_create_context.txt
#pragma once

#include "Nucleus/Configuration.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Nucleus/Status.h"

#define WGL_CONTEXT_MAJOR_VERSION_ARB           0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB           0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB             0x2093
#define WGL_CONTEXT_FLAGS_ARB                   0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB            0x9126

#define WGL_CONTEXT_DEBUG_BIT_ARB               0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  0x0002

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB        0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

#define ERROR_INVALID_VERSION_ARB               0x2095
#define ERROR_INVALID_PROFILE_ARB               0x2096
    
typedef HGLRC (WINAPI *WGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext,
                                                       const int *attribList);

extern WGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

Nucleus_Status initialize_WGL_ARB_create_context();
                                          
#endif
