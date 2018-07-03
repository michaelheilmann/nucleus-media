#pragma once

#include "Nucleus.Media.Plugin.OpenGL/VideoSystemWindow.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) 

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>

#endif
