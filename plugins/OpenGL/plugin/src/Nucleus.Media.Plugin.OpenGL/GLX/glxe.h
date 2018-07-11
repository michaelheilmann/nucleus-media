#pragma once

#include "Nucleus/Configuration.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>

/// @brief An OpenGL version.
typedef struct glxe_gl_version
{
	/// @brief The OpenGL major version number.
	int major;
	/// @brief The OpenGL minor version number.
	int minor;
} glxe_gl_version;

/// @brief A GLX version.
typedef struct glxe_glx_version
{
	/// @brief The GLX major version number.
	int major;
	/// @brief The GLX minor version number.
	int minor;
} glxe_glx_version;

/// @brief Get the number of known OpenGL versions.
/// @return the number of known OpenGL versions
size_t glxe_get_num_gl_versions();

/// @brief Get the OpenGL version at the specified index.
/// @param index the index of the OpenGL version. Must be within the bounds of 0 (incl.) and glxe_get_num_gl_versions() (excl.).
/// @return pointer to a static constant glxe_gl_version object
const glxe_gl_version *glxe_get_gl_version(size_t index);

/// @brief Create an OpenGL context.
/// @detail Try to create contexts for OpenGL versions from the highest version to the lowest version.
/// The first successfully created context is returned.
/// If @a direct is @a True, then only direct contexts are considered.
GLXContext glxe_create_context_with_configuration(Display *dpy, GLXFBConfig cfg, Bool direct);

Window glxe_create_window(Display *display, XVisualInfo *visualInfo);


#endif
