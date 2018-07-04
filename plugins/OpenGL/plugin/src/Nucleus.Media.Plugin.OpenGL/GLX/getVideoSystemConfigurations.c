#include "Nucleus.Media.Plugin.OpenGL/GLX/getVideoSystemConfigurations.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) 

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <stdio.h>

#include "Nucleus/Media/VideoSystemConfiguration.h"

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
    Nucleus_Status status;
    //
    Display *sourceDisplay = XOpenDisplay(NULL);
    if (!sourceDisplay)
    {
        fprintf(stderr, "unable to open display\n");
        return Nucleus_Status_EnvironmentFailed;
    }
    // Frame buffer configurations were added in GLX version 1.3.
    int major, minor;
    if (!glXQueryVersion(sourceDisplay, &major, &minor) || 
        ((major == 1) && (minor < 3)) || (major < 1))
    {
        fprintf(stderr, "invalid GLX version\n");
        return Nucleus_Status_EnvironmentFailed;
    }
    // Get the frame buffer configurations.
    int numberOfSourceConfigurations;
    GLXFBConfig *sourceConfigurations = glXChooseFBConfig(sourceDisplay,
                                                          DefaultScreen(sourceDisplay),
                                                          NULL,
                                                          &numberOfSourceConfigurations);
    if (!sourceConfigurations)
    {
        fprintf(stderr, "unable to find a frame buffer configuration\n");
        return Nucleus_Status_EnvironmentFailed;
    }
    for (int i = 0, n = numberOfSourceConfigurations; i < n; ++i)
    {
        XVisualInfo *sourceVisualInfo = glXGetVisualFromFBConfig(sourceDisplay,
                                                                 sourceConfigurations[i]);
        if (sourceVisualInfo)
        {
            Nucleus_Media_VideoSystemConfiguration *configuration;

            status = Nucleus_Media_VideoSystemConfiguration_create(&configuration);
            if (Nucleus_Unlikely(status))
            {
                XFree(sourceVisualInfo);
                XFree(sourceConfigurations);
                XCloseDisplay(sourceDisplay);
                return status;
            }
            
            status = getConfiguration(configuration, sourceDisplay, sourceConfigurations[i]);
            if (Nucleus_Unlikely(status))
            {
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configuration));
                XFree(sourceVisualInfo);
                XFree(sourceConfigurations);
                XCloseDisplay(sourceDisplay);
                return status;
            }
			
			status = Nucleus_ObjectArray_append(configurations, NUCLEUS_OBJECT(configuration));
			Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configuration));
			if (Nucleus_Unlikely(status))
			{
				XFree(sourceVisualInfo);
				XFree(sourceConfigurations);
				XCloseDisplay(sourceDisplay);
				return status;
			}
			
            XFree(sourceVisualInfo);
        }
    }
    //
    XFree(sourceConfigurations);
    XCloseDisplay(sourceDisplay);
    //
    return Nucleus_Status_Success;
}

#endif
