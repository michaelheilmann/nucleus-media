#include "Nucleus.Media.Plugin.OpenGL/GLX/glxe.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)

#include <stdio.h>
#include <string.h>
#include "Nucleus.Media.Plugin.OpenGL/GLX/GLX_ARB_create_context.h"

#define ERROR(...) \
    fprintf(stderr, "[%s, %s, %d] ", "GIL", __FILE__, __LINE__); \
    fprintf(stderr, __VA_ARGS__);

#define INFO(...) \
    fprintf(stdout, "[%s, %s, %d] ", "GIL", __FILE__, __LINE__); \
    fprintf(stdout, __VA_ARGS__);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* List of known OpenGL versions. */
static const glxe_gl_version _gl_versions[] =
{
   {4, 6},
   {4, 5},
   {4, 4},
   {4, 3},
   {4, 2},
   {4, 1},
   {4, 0},

   {3, 3},
   {3, 2},
   {3, 1},
   {3, 0},

   {2, 1},
   {2, 0},

   {1, 5},
   {1, 4},
   {1, 3},
   {1, 2},
   {1, 1},
   {1, 0},
};

/* Size of list of known OpenGL versions. */
static const size_t _num_gl_versions = sizeof(_gl_versions) / sizeof(glxe_gl_version);

glxe_glx_version *glxe_get_glx_version(Display *display)
{
    if (!display)
    {
        ERROR(u8"invalid argument %s", u8"NULL == display");
        return NULL;
    }
    int majorVersion, minorVersion;
    if (!glXQueryVersion(display, &majorVersion, &minorVersion))
    {
        ERROR(u8"%s failed\n", u8"glXQueryVersion");
        return NULL;
    }
    glxe_glx_version *version = malloc(sizeof(glxe_glx_version));
    if (!version)
    {
        ERROR(u8"%s failed", u8"malloc");
        return NULL;
    }
    version->major = majorVersion;
    version->minor = minorVersion;
    return version;
}

size_t glxe_get_num_known_gl_versions()
{ return _num_gl_versions; }

const glxe_gl_version *glxe_get_known_gl_version(size_t index)
{ return &(_gl_versions[index]); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static int createContextErrorHandler(Display *display, XErrorEvent *event)
{ return 0; }

GLXContext glxe_create_context_with_configuration(Display *display, GLXFBConfig configuration, Bool direct)
{
	Nucleus_Status status;
	/*Try a 3.x core profile. */
	status = initialize_GLX_ARB_create_context(display);
	if (!status)
	{
		for (size_t i = 0, n = glxe_get_num_known_gl_versions(); i < n; ++i)
		{
			const glxe_gl_version *version = glxe_get_known_gl_version(i);
			if (version->major >= 3)
			{
				int attributes[] =
				{
					GLX_CONTEXT_MAJOR_VERSION_ARB, version->major,
					GLX_CONTEXT_MINOR_VERSION_ARB, version->minor,
					None,
				};
				// If we invoke glXCreateContextAttribsARB and it fails, then we need to have the
                // create_context_error_handler in place, otherwise the program terminates.
				int (*oldErrorHandler)(Display *, XErrorEvent *) = XSetErrorHandler(createContextErrorHandler);
				GLXContext context = glXCreateContextAttribsARB(display, configuration, NULL, True, attributes);
				XSetErrorHandler(oldErrorHandler);
				if (context)
				{
                    INFO(u8"able to create an OpenGL %d.%d context\n", (int)version->major, (int)version->minor);
					if (direct && !glXIsDirect(display, context))
					{
						glXDestroyContext(display, context);
						return 0;
					}
					return context;
				}
                ERROR(u8"unable to create an OpenGL %d.%d context\n", (int)version->major, (int)version->minor);
			}
		}
	}
	else
	{
		ERROR(u8"extension %s not supported\n", u8"GLX_ARB_create_context_profile");
	}
	
	/* Create a context using glXCreateNewContext. */
	GLXContext context = glXCreateNewContext(display, configuration, GLX_RGBA_TYPE, NULL, direct);
    /* Make sure the context is direct, if direct was requested. */
    if (context && direct)
    {
		if (!glXIsDirect(display, context))
		{
			glXDestroyContext(display, context);
			return 0;
		}
   }
   return context;
}

Window glxe_create_window(Display *display, XVisualInfo *visualInfo)
{
	if (!display || !visualInfo) return 0;

	// Get the root window.
	Window rootWindow = RootWindow(display, visualInfo->screen);

    // Create a color map.
    Colormap colormap = XCreateColormap(display,
	                                    rootWindow, 
                                        visualInfo->visual,
										AllocNone);
	// Set the window attributes.
    XSetWindowAttributes setWindowAttributes;
    setWindowAttributes.colormap = colormap;
    setWindowAttributes.background_pixmap = None ;
    setWindowAttributes.border_pixel = 0;
    setWindowAttributes.event_mask = StructureNotifyMask;
	
	// Create the window.
	Window window = XCreateWindow(display,
	                              rootWindow, 
                                  0,
								  0,
								  100,
								  100,
								  0,
								  visualInfo->depth,
								  InputOutput, 
                                  visualInfo->visual, 
                                  CWBorderPixel |CWColormap | CWEventMask,
								  &setWindowAttributes);
    if (!window)
    {
        ERROR(u8"%s failed\n", u8"XCreateWindow");
    }

	// Return the window.
	return window;
}

char *glxe_get_glx_server_vendor_name(Display *display, int screenNumber)
{
    const char *name = glXQueryServerString(display, screenNumber, GLX_VENDOR);
    if (!name)
    {
        ERROR("%s failed\n", "glXQueryServerString");
        return NULL;
    }
    return strdup(name);
}

char *glxe_get_glx_client_vendor_name(Display *display)
{
    const char *name = glXGetClientString(display, GLX_VENDOR);
    if (!name)
    {
        ERROR("%s failed\n", "glXGetClientString");
        return NULL;
    }
    return strdup(name);     
}

char *glxe_get_gl_vendor_name()
{
    const char *name = (const char *)glGetString(GL_VENDOR);
    if (!name)
    {
        ERROR("%s failed\n", "glGetString");
        return NULL;
    }
    return strdup(name);    
}


char *glxe_get_glx_server_extensions(Display *display, int screenNumber)
{
    const char *extensions = glXQueryServerString(display, screenNumber, GLX_EXTENSIONS);
    if (!extensions)
    {
        ERROR("%s failed\n", "glXQueryServerString");
        return NULL;
    }
    return strdup(extensions);
}

char *glxe_get_glx_client_extensions(Display *display)
{
    const char *extensions = glXGetClientString(display, GLX_EXTENSIONS);
    if (!extensions)
    {
        ERROR("%s failed\n", "glXGetClientString");
        return NULL;
    }
    return strdup(extensions);
}

char *glxe_get_glx_extensions(Display *display, int screenNumber)
{
    const char *extensions = glXQueryExtensionsString(display, screenNumber);
    if (!extensions)
    {
        ERROR("%s failed\n", "glXQueryExtensionsString");
        return NULL;
    }
    return strdup(extensions);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

glxe_glx_server_version *glxe_get_glx_server_version(Display *display, int screenNumber)
{
    const char *version_string = glXQueryServerString(display, screenNumber, GLX_VERSION);
    if (!version_string)
    {
        ERROR("%s failed\n", "glXQueryServerString");
        return NULL;
    }
    int version_major, version_minor;
    if (2 != sscanf(version_string, "%d.%d", &version_major, &version_minor))
    {
        ERROR("%s failed\n", "sscanf");
        return NULL;
    }
    glxe_glx_server_version *version = malloc(sizeof(glxe_glx_server_version));
    if (!version)
    {
        ERROR("%s failed\n", "malloc");
        return NULL;
    }
    version->major = version_major;
    version->minor = version_minor;
    return version;
}

void glxe_free_glx_server_version(glxe_glx_server_version *version)
{ free(version); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

glxe_glx_client_version *glxe_get_glx_client_version(Display *display)
{
    const char *version_string = glXGetClientString(display, GLX_VERSION);
    if (!version_string)
    {
        ERROR("%s failed\n", "glXGetClientString");
        return NULL;
    }
    int version_major, version_minor;
    if (2 != sscanf(version_string, "%d.%d", &version_major, &version_minor))
    {
        ERROR("%s failed\n", "sscanf");
        return NULL;
    }
    glxe_glx_client_version *version = malloc(sizeof(glxe_glx_client_version));
    if (!version)
    {
        ERROR("%s failed\n", "malloc");
        return NULL;
    }
    version->major = version_major;
    version->minor = version_minor;
    return version;
}

void glxe_free_glx_client_version(glxe_glx_client_version *version)
{ free(version); }

#endif
