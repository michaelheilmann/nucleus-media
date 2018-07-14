#pragma once

#include "Nucleus/Configuration.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)

#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/// @return a pointer to the server vendor name string on success, a null pointer on failure
/// @remark A server vendor name string returned by this functions must be deallocated using free when it is no longer required.
char *glxe_get_glx_server_vendor_name(Display *display, int screenNumber);

/// @return a pointer to the client vendor name string on success, a null pointer on failure
/// @remark A client vendor name string returned by this functions must be deallocated using free when it is no longer required.
char *glxe_get_glx_client_vendor_name(Display *display);

/// @return a pointer to a GLX server extensions string on success, a null pointer on failure
/// @remark A GLX server extensions string returned by this functions must be deallocated using free when it is no longer required.
char *glxe_get_glx_server_extensions(Display *display, int screenNumber);

/// @return a pointer t a GLX client extensions string on success, a null pointer on failure
/// @remark A GLX client extensions string returned by this functions must be deallocated using free when it is no longer required.
char *glxe_get_glx_client_extensions(Display *display);

/// @return a pointer t a GLX extensions string on success, a null pointer on failure
/// @remark A GLX extensions string returned by this functions must be deallocated using free when it is no longer required.
/// @remark glxe_get_glx_server_extensions() (the server side) and glx_get_glx_client_extensions() (the client side) are of
/// limited value to programs, which want to use an extension. The effectively available extensions are determined by the
/// connection (of the client and the server). glx_get_glx_extensions() retrieves the list of effectively available extensions
/// of a connection.
char *glxe_get_glx_extensions(Display *display, int screenNumber);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A GLX server version number.
typedef struct glxe_glx_server_version
{
	/// @brief The GLX major server version number.
	int major;
	/// @brief The GLX minor server version number.
	int minor;
}glxe_glx_server_version;

/// @return a pointer to the server version on success, a null pointer on failure
/// @remark A glxe_glx_server_version object returned by this functions must be deallocated using glxe_free_glx_server_version() when it is no longer required.
glxe_glx_server_version *glxe_get_glx_server_version(Display *display, int screenNumber);

/// @param version a pointer to a glxe_glx_server_version object
void glxe_free_glx_server_version(glxe_glx_server_version *version);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A GLX client version number.
typedef struct glxe_glx_client_version
{
	/// @brief The GLX major client version number.
	int major;
	/// @brief The GLX minor client version number.
	int minor;
} glxe_glx_client_version;

/// @return a pointer to the client vendor name string on success, a null pointer on failure
/// @remark A glxe_glx_client_version object returned by this functions must be deallocated using glxe_free_glx_client_version() when it is no longer required.
glxe_glx_client_version *glxe_get_glx_client_version(Display *display);

/// @param version a pointer to a glxe_glx_client_version object
void glxe_free_glx_client_version(glxe_glx_client_version *version);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A GLX version.
typedef struct glxe_glx_version
{
	/// @brief The GLX major version number.
	int major;
	/// @brief The GLX minor version number.
	int minor;
} glxe_glx_version;

/// @brief Get the GLX version.
/// @return a pointer to a glxe_glx_version on success, a null pointer on failure
/// @remark A glxe_glx_version object returned by this functions must be deallocated using free when it is no longer required.
glxe_glx_version *glxe_get_glx_version();

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief An OpenGL version.
typedef struct glxe_gl_version
{
	/// @brief The OpenGL major version number.
	int major;
	/// @brief The OpenGL minor version number.
	int minor;
} glxe_gl_version;

/// @brief Get the number of known OpenGL versions.
/// @return the number of known OpenGL versions
size_t glxe_get_num_known_gl_versions();

/// @brief Get the OpenGL version at the specified index.
/// @param index the index of the OpenGL version. Must be within the bounds of 0 (incl.) and glxe_get_num_gl_versions() (excl.).
/// @return pointer to a static constant glxe_gl_version object on success, a null pointer on failure
const glxe_gl_version *glxe_get_known_gl_version(size_t index);

/// @brief Create an OpenGL context.
/// @detail Try to create contexts for OpenGL versions from the highest version to the lowest version.
/// The first successfully created context is returned.
/// If @a direct is @a True, then only direct contexts are considered.
GLXContext glxe_create_context_with_configuration(Display *dpy, GLXFBConfig cfg, Bool direct);

Window glxe_create_window(Display *display, XVisualInfo *visualInfo);


#endif
