#include "Nucleus.Media.Plugin.OpenGL/GLX/getVideoSystemConfigurations.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) 

#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <stdio.h>
#include "Nucleus.Media.Plugin.OpenGL/GLX/glxe.h"

#include "Nucleus/Media/VideoSystemConfiguration.h"

typedef struct _Window _Window;
struct _Window
{
    Display *display;
    int numberOfFrameBufferConfigurations;
    GLXFBConfig *frameBufferConfigurations;
    GLXFBConfig frameBufferConfiguration;
    XVisualInfo *visualInfo;
    Window window;
    GLXContext glxContext;
	struct
	{
		struct
		{
			int major;
			int minor;
		} version;
	} glx;
}; // struct _Window


static void ChooseFbConfig(Display *dpy, GLXFBConfig **cfgs, int *cfgsCount)
{
    // Get all framebuffer configurations.
	static int doubleBuffered[] =
    {
      GLX_X_RENDERABLE, True, /* Ensure we can draw to windows or pixmaps. */
      GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT, /* Ensure we can draw to windows. */
      GLX_RENDER_TYPE, GLX_RGBA_BIT, /* Do not consider RGBA contexts (do not consider indexed colors). */
      /*GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,*/
      GLX_RED_SIZE, 8,
      GLX_GREEN_SIZE, 8,
      GLX_BLUE_SIZE, 8,
      GLX_ALPHA_SIZE, 8,
      GLX_DEPTH_SIZE, 24,
      GLX_STENCIL_SIZE, 8,
      GLX_DOUBLEBUFFER, True,
      None
    };
	static int singleBuffered[] =
    {
      GLX_X_RENDERABLE, True, /* Ensure we can draw to windows or pixmaps. */
      GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT, /* Ensure we can draw to windows. */
      GLX_RENDER_TYPE, GLX_RGBA_BIT, /* Do not consider RGBA contexts (do not consider indexed colors). */
      /*GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,*/
      GLX_RED_SIZE, 8,
      GLX_GREEN_SIZE, 8,
      GLX_BLUE_SIZE, 8,
      GLX_ALPHA_SIZE, 8,
      GLX_DEPTH_SIZE, 24,
      GLX_STENCIL_SIZE, 8,
      GLX_DOUBLEBUFFER, False,
      None
    };
	*cfgs = glXChooseFBConfig(dpy, DefaultScreen(dpy), doubleBuffered, cfgsCount);
    if (!*cfgs)
    {
		*cfgs = glXChooseFBConfig(dpy, DefaultScreen(dpy), singleBuffered, cfgsCount);
    }
}

static Nucleus_Status _Window_initialize(_Window *window)
{
    // Open default display.
    window->display = XOpenDisplay(NULL);
    if (!window->display)
    {
        fprintf(stderr, u8"%s failed\n", u8"XOpenDisplay");
        return Nucleus_Status_EnvironmentFailed;
    }
    // As frame buffer configurations are not available before GLX version 1.3:
    // Assert GLX version is greater than or equal to 1.3.
    glxe_glx_version *glx_version = glxe_get_glx_version();
    if (!glx_version)
    {
        return Nucleus_Status_EnvironmentFailed;
    }
    if (((glx_version->major == 1) && (glx_version->minor < 3)) || (glx_version->major < 1))
    {
        fprintf(stderr, u8"GLX version 1.3 or higher required. GLX version %d.%d given\n", 
                        glx_version->major, glx_version->minor);
        free(glx_version);
        XCloseDisplay(window->display);
        window->display = NULL;
        return Nucleus_Status_EnvironmentFailed;
    }
    free(glx_version);
	ChooseFbConfig(window->display, &window->frameBufferConfigurations, &window->numberOfFrameBufferConfigurations);
    if (!window->frameBufferConfigurations)
    {
        fprintf(stderr, u8"%s failed\n", u8"glXChooseFBConfig");
        XCloseDisplay(window->display);
        window->display = NULL;
        return Nucleus_Status_EnvironmentFailed;
    }
    if (0 == window->frameBufferConfigurations)
    {
        fprintf(stderr, u8"%s failed\n", u8"glXChooseFBConfig");
        XFree(window->frameBufferConfigurations);
        window->frameBufferConfigurations = NULL;
        XCloseDisplay(window->display);
        window->display = NULL;
        return Nucleus_Status_EnvironmentFailed;        
    }
    // Create visual.
    window->frameBufferConfiguration = window->frameBufferConfigurations[0];
    window->visualInfo = glXGetVisualFromFBConfig(window->display, window->frameBufferConfiguration);
    if (!window->visualInfo)
    {
        fprintf(stderr, u8"%s failed\n", u8"glXGetVisualFromFBConfig");
        XFree(window->frameBufferConfigurations);
        window->frameBufferConfigurations = NULL;
        XCloseDisplay(window->display);
        window->display = NULL;
        return Nucleus_Status_EnvironmentFailed; 
    }
    //
	window->window = glxe_create_window(window->display, window->visualInfo);
	if (!window->window)
    {
        fprintf(stderr, u8"%s failed\n", u8"glxe_create_window");
        XFree(window->frameBufferConfigurations);
        window->frameBufferConfigurations = NULL;
        XCloseDisplay(window->display);
        window->display = NULL;
        return Nucleus_Status_EnvironmentFailed; 
    }
	// Try direct context.
	window->glxContext = glxe_create_context_with_configuration(window->display, window->frameBufferConfiguration, True);
    if (!window->glxContext)
    {
		// Try indirect context.
		window->glxContext = glxe_create_context_with_configuration(window->display, window->frameBufferConfiguration, False);
		if (!window->glxContext)
		{
			fprintf(stderr, u8"%s failed\n", u8"glXCreateContext");
			XDestroyWindow(window->display, window->window);
			window->window = 0;
			XFree(window->frameBufferConfigurations);
			window->frameBufferConfigurations = NULL;
			XCloseDisplay(window->display);
			window->display = NULL;
			return Nucleus_Status_EnvironmentFailed;
		}			
    }
    if (!glXMakeCurrent(window->display, window->window, window->glxContext))
    {
        fprintf(stderr, u8"%s failed\n", u8"glXMakeCurrent");
        glXDestroyContext(window->display, window->glxContext);
        window->glxContext = NULL;
        XDestroyWindow(window->display, window->window);
        window->window = 0;
        XFree(window->frameBufferConfigurations);
        window->frameBufferConfigurations = NULL;
        XCloseDisplay(window->display);
        window->display = NULL;
        return Nucleus_Status_EnvironmentFailed;        
    }
    {
        // The server.
        char *serverVendorName = glxe_get_glx_server_vendor_name(window->display, DefaultScreen(window->display));
        if (serverVendorName)
        {
            fprintf(stdout, "GLX server vendor name: %s\n", serverVendorName);
            free(serverVendorName);
        }
        else
        {
            fprintf(stdout, "GLX server vendor name: %s\n", "n/a");
        }
        glxe_glx_server_version *serverVersion = glxe_get_glx_server_version(window->display, DefaultScreen(window->display));
        if (serverVersion)
        {
            fprintf(stdout, "GLX server version: %d.%d\n", serverVersion->major, serverVersion->minor);
            glxe_free_glx_server_version(serverVersion);
        }
        else
        {
            fprintf(stdout, "GLX server version: %s\n", "n/a");
        }
        char *serverExtensions = glxe_get_glx_server_extensions(window->display, DefaultScreen(window->display));
        if (serverExtensions)
        {
            fprintf(stdout, "GLX server extensions: %s\n", serverExtensions);
            free(serverExtensions);
        }
        else
        {
            fprintf(stdout, "GLX server extensions: %s\n", "n/a");            
        }
        // The client.
        char *clientVendorName = glxe_get_glx_client_vendor_name(window->display);
        if (clientVendorName)
        {
            fprintf(stdout, "GLX client vendor name: %s\n", clientVendorName);
            free(clientVendorName);
        }
        else
        {
            fprintf(stdout, "GLX client vendor name: %s\n", "n/a");           
        }
        glxe_glx_client_version *clientVersion = glxe_get_glx_client_version(window->display);
        if (clientVersion)
        {
            fprintf(stdout, "GLX client version: %d.%d\n", clientVersion->major, clientVersion->minor);
            glxe_free_glx_client_version(clientVersion);
        }
        else
        {
            fprintf(stdout, "GLX client vendor name: %s\n", "n/a");    
        }
        char *clientExtensions = glxe_get_glx_client_extensions(window->display);
        if (clientExtensions)
        {
            fprintf(stdout, "GLX client extensions: %s\n", clientExtensions);
            free(clientExtensions);
        }
        else
        {
            fprintf(stdout, "GLX client extensions: %s\n", "n/a");            
        }
        // The connection.
        char *extensions = glxe_get_glx_extensions(window->display, DefaultScreen(window->display));
        if (extensions)
        {
            fprintf(stdout, "GLX extensions: %s\n", extensions);
            free(extensions);            
        }
        else
        {
            fprintf(stdout, "GLX extensions: %s\n", "n/a");
        }
        // GL.
        char *glVendorName = glxe_get_gl_vendor_name();
        if (glVendorName)
        {
            fprintf(stdout, "GL vendor: %s\n", glVendorName);
            free(glVendorName);
        }
        else
        {
            fprintf(stdout, "GL vendor: %s\n", "n/a");           
        }
        char *glRendererName = glxe_get_gl_renderer_name();
        if (glRendererName)
        {
            fprintf(stdout, "GL renderer: %s\n", glRendererName);
            free(glRendererName);
        }
        else
        {
            fprintf(stdout, "GL renderer: %s\n", "n/a");           
        }
    }
    // Process any errors.
    XSync(window->display, False);
    //
    // Return success.
    return Nucleus_Status_Success;
}

static Nucleus_Status _Window_uninitialize(_Window *window)
{
    glXMakeCurrent(window->display, 0, NULL);
    glXDestroyContext(window->display, window->glxContext);
    window->glxContext = NULL;
    XDestroyWindow(window->display, window->window);
    window->window = 0;
    XFree(window->visualInfo);
    window->visualInfo = NULL;
    XFree(window->frameBufferConfigurations);
    window->frameBufferConfigurations = NULL;
    XCloseDisplay(window->display);
    window->display = NULL;
    return Nucleus_Status_Success;
}

static Nucleus_Status
getConfiguration
    (
        Nucleus_Media_VideoSystemConfiguration *target,
        Display *sourceDisplay,
        GLXFBConfig sourceFrameBufferConfiguration
    );

static Nucleus_Status
getConfiguration
    (
        Nucleus_Media_VideoSystemConfiguration *target,
        Display *sourceDisplay,
        GLXFBConfig sourceFrameBufferConfiguration
    )
{
    Nucleus_Status status;
    int temporary;

    glXGetFBConfigAttrib(sourceDisplay, sourceFrameBufferConfiguration, GLX_SAMPLE_BUFFERS, &temporary);
    status = Nucleus_Media_VideoSystemConfiguration_setNumberOfSampleBuffers(target, temporary);
    if (Nucleus_Unlikely(status)) { return status; }
    
    glXGetFBConfigAttrib(sourceDisplay, sourceFrameBufferConfiguration, GLX_SAMPLES, &temporary);
    status = Nucleus_Media_VideoSystemConfiguration_setNumberOfSamples(target, temporary);
    if (Nucleus_Unlikely(status)) { return status; }
    
    glXGetFBConfigAttrib(sourceDisplay, sourceFrameBufferConfiguration, GLX_RED_SIZE, &temporary);
    status = Nucleus_Media_VideoSystemConfiguration_setRedBits(target, temporary);
    if (Nucleus_Unlikely(status)) { return status; }
    
    glXGetFBConfigAttrib(sourceDisplay, sourceFrameBufferConfiguration, GLX_GREEN_SIZE, &temporary);
    status = Nucleus_Media_VideoSystemConfiguration_setGreenBits(target, temporary);
    if (Nucleus_Unlikely(status)) { return status; }
    
    glXGetFBConfigAttrib(sourceDisplay, sourceFrameBufferConfiguration, GLX_BLUE_SIZE, &temporary);
    status = Nucleus_Media_VideoSystemConfiguration_setBlueBits(target, temporary);
    if (Nucleus_Unlikely(status)) { return status; }
    
    glXGetFBConfigAttrib(sourceDisplay, sourceFrameBufferConfiguration, GLX_ALPHA_SIZE, &temporary);
    status = Nucleus_Media_VideoSystemConfiguration_setAlphaBits(target, temporary);
    if (Nucleus_Unlikely(status)) { return status; }
    
    glXGetFBConfigAttrib(sourceDisplay, sourceFrameBufferConfiguration, GLX_DEPTH_SIZE, &temporary);
    status = Nucleus_Media_VideoSystemConfiguration_setDepthBits(target, temporary);
    if (Nucleus_Unlikely(status)) { return status; }
    
    glXGetFBConfigAttrib(sourceDisplay, sourceFrameBufferConfiguration, GLX_STENCIL_SIZE, &temporary);
    status = Nucleus_Media_VideoSystemConfiguration_setStencilBits(target, temporary);
    if (Nucleus_Unlikely(status)) { return status; }
    
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
getVideoSystemConfigurations
    (
		Nucleus_ObjectArray *configurations
    )
{
    _Window window;
    Nucleus_Status status;
    //
    status = _Window_initialize(&window);
    if (Nucleus_Unlikely(status)) return status;
    for (int i = 0, n = window.numberOfFrameBufferConfigurations; i < n; ++i)
    {
        XVisualInfo *sourceVisualInfo = glXGetVisualFromFBConfig(window.display,
                                                                 window.frameBufferConfigurations[i]);
        if (sourceVisualInfo)
        {
            Nucleus_Media_VideoSystemConfiguration *configuration;

            status = Nucleus_Media_VideoSystemConfiguration_create(&configuration);
            if (Nucleus_Unlikely(status))
            {
                XFree(sourceVisualInfo);
                _Window_uninitialize(&window);
                return status;
            }
            
            status = getConfiguration(configuration, window.display, window.frameBufferConfigurations[i]);
            if (Nucleus_Unlikely(status))
            {
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configuration));
                XFree(sourceVisualInfo);
                _Window_uninitialize(&window);
                return status;
            }
			
			status = Nucleus_ObjectArray_append(configurations, NUCLEUS_OBJECT(configuration));
			Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configuration));
			if (Nucleus_Unlikely(status))
			{
				XFree(sourceVisualInfo);
                _Window_uninitialize(&window);
				return status;
			}
			
            XFree(sourceVisualInfo);
        }
    }
    //
    _Window_uninitialize(&window);
    //
    return Nucleus_Status_Success;
}

#endif
