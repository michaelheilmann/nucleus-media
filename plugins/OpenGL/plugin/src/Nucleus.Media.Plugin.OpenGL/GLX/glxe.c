#include "Nucleus.Media.Plugin.OpenGL/GLX/glxe.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)

#include "Nucleus.Media.Plugin.OpenGL/GLX/GLX_ARB_create_context.h"

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

size_t glxe_get_num_gl_versions()
{ return _num_gl_versions; }

const glxe_gl_version *glxe_get_gl_version(size_t index)
{ return &(_gl_versions[index]); }

static int createContextErrorHandler(Display *display, XErrorEvent *event)
{ return 0; }

GLXContext glxe_create_context_with_configuration(Display *display, GLXFBConfig configuration, Bool direct)
{
	Nucleus_Status status;
	/*Try a 3.x core profile. */
	status = initialize_GLX_ARB_create_context(display);
	if (!status)
	{
		for (size_t i = 0, n = glxe_get_num_gl_versions(); i < n; ++i)
		{
			const glxe_gl_version *version = glxe_get_gl_version(i);
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
					if (direct && !glXIsDirect(display, context))
					{
						glXDestroyContext(display, context);
						return 0;
					}
					return context;
				}
				fprintf(stderr, "[GLX Extension Library, %s, %d] unable to create an OpenGL %d.%d context\n", __FILE__, __LINE__, (int)version->major, (int)version->minor);
			}
		}
	}
	else
	{
		fprintf(stderr, "[GLX Extension Library, %s, %d] extension %s not supported\n", __FILE__, __LINE__, "GLX_ARB_create_context_profile");
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
        fprintf(stderr, u8"[GLX extension library, %s, %d] %s failed\n", __FILE__, __LINE__, u8"XCreateWindow");
    }

	// Return the window.
	return window;
}

#endif
