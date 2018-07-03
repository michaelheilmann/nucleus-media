#include "Nucleus.Media.Plugin.OpenGL/WGL/getVideoSystemConfigurations.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS) 

#include <stdio.h>

#include <Windows.h>
#include <WinUser.h>

#include <GL/glew.h>
#include <GL/wglew.h>

#include "Nucleus/Memory.h"

#include "Nucleus/Media/VideoSystemConfiguration.h"

typedef struct TemporaryWindow
{
    ATOM wndclass;
    HWND hWnd;
    HDC hDC;
    PIXELFORMATDESCRIPTOR pfd;
    int pfdId;
    HGLRC hGLRC;
} TemporaryWindow;

LRESULT CALLBACK TemporaryWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;       // message handled
}

Nucleus_NonNull() static Nucleus_Status
getConfiguration
    (
        Nucleus_Media_VideoSystemConfiguration *target,
        int pixelFormatId
    );

Nucleus_NonNull() static Nucleus_Status
getConfiguration
    (
        Nucleus_Media_VideoSystemConfiguration *target,
        int pixelFormatId
    )
{
    return Nucleus_Status_Success;
}

Nucleus_Status
getConfigurations
    (
        Nucleus_ObjectArray *configurations
    )
{
    Nucleus_Status status;
    static const LPCSTR TITLE = "Nucleus: Media - Plugin: OpenGL - Temporary Window";
    static const LPCSTR CLASSNAME = "Nucleus.Media.Plugin.OpenGL.TemporaryWindow";
    // Get the module handle.
    HINSTANCE hInstance = GetModuleHandle(NULL);
    // Configure the window class.
    WNDCLASSEXA wndclassex;
    ZeroMemory(&wndclassex, sizeof(wndclassex));
    wndclassex.cbSize = sizeof(wndclassex);
    wndclassex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclassex.hInstance = hInstance;
    wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclassex.lpfnWndProc = &TemporaryWindowProcedure;
    wndclassex.lpszClassName = CLASSNAME;
    TemporaryWindow window;
    window.hGLRC = NULL;
    window.hDC = NULL;
    window.hWnd = NULL;
    window.pfdId = 0;
    window.wndclass = 0;
    // Register window class.
    window.wndclass = RegisterClassExA(&wndclassex);
    if (!window.wndclass)
    {
        fprintf(stderr, "unable to register window class\n");
        status = Nucleus_Status_EnvironmentFailed;
        goto End;
    }
    // Create window.
    window.hWnd = CreateWindowA(CLASSNAME, // Window class name.
                                TITLE, // Window title.
                                WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // Window style.
                                0, 0, // left and top position.
                                1, 1, // width and height.
                                NULL, // Parent window handle.
                                NULL, // Menu handle.
                                hInstance, // Module handle.
                                NULL); // Creation parameters.
    if (!window.hWnd)
    {
        fprintf(stderr, "unable to create window\n");
        status = Nucleus_Status_EnvironmentFailed;
        goto End;
    }
    // Create device context.
    window.hDC = GetDC(window.hWnd);
    if (!window.hDC)
    {
        fprintf(stderr, "unable to create window\n");
        status = Nucleus_Status_EnvironmentFailed;
        goto End;
    }
    // Select pixel format.
    ZeroMemory(&window.pfd, sizeof(window.pfd));
    window.pfd.nSize = sizeof(window.pfd);
    window.pfd.nVersion = 1;
    window.pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    window.pfd.iPixelType = PFD_TYPE_RGBA;
    window.pfd.cColorBits = 32;
    window.pfd.cAlphaBits = 8;
    window.pfd.cDepthBits = 24;
    window.pfdId = ChoosePixelFormat(window.hDC, &window.pfd);
    if (0 == window.pfdId)
    {
        fprintf(stderr, "unable to select pixel format\n");
        status = Nucleus_Status_EnvironmentFailed;
        goto End;
    }
    // Set pixel format.
    if (FALSE == SetPixelFormat(window.hDC, window.pfdId, &window.pfd))
    {
        fprintf(stderr, "unable to set pixel format\n");
        status = Nucleus_Status_EnvironmentFailed;
        goto End;
    }
    // Create WGL context.
    window.hGLRC = wglCreateContext(window.hDC);
    if (!window.hGLRC)
    {
        fprintf(stderr, "unable to create WGL context\n");
        status = Nucleus_Status_EnvironmentFailed;
        goto End;
    }
    if (false == wglMakeCurrent(window.hDC, window.hGLRC))
    {
        fprintf(stderr, "unable to make WGL context current\n");
        status = Nucleus_Status_EnvironmentFailed;
        goto End;
    }
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "unable to make WGL context current\n");
        status = Nucleus_Status_EnvironmentFailed;
        goto End;
    }
    static const int attribs[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 1,
        WGL_CONTEXT_FLAGS_ARB, 0,
        0
    };
    if (wglewIsSupported("WGL_ARB_pixel_format") != 1)
    {
        fprintf(stderr, "WGL_ARB_pixel_format not supported\n");
        status = Nucleus_Status_EnvironmentFailed;
        goto End;
    }
    // Get the number of pixel formats.
    int numberOfPixelFormats;
    static const int ATTRIBUTES[] = { WGL_NUMBER_PIXEL_FORMATS_ARB };
    if (FALSE == wglGetPixelFormatAttribivARB(window.hDC, 0, 0, 1, ATTRIBUTES, &numberOfPixelFormats))
    {
        fprintf(stderr, "wglGetPixelFormatAttribivARB failed\n");
        status = Nucleus_Status_EnvironmentFailed;
        goto End;
    }
    int *pixelFormats;
    status = Nucleus_allocateArrayMemory((void **)&pixelFormats, numberOfPixelFormats, sizeof(int));
    if (Nucleus_Unlikely(status))
    {
        fprintf(stderr, "Nucleus_allocateArrayMemory failed\n");
        status = Nucleus_Status_EnvironmentFailed;
        goto End;
    }
    UINT actualNumberOfFormats;
    if (FALSE == wglChoosePixelFormatARB(window.hDC, NULL, NULL, numberOfPixelFormats, pixelFormats, &actualNumberOfFormats))
    {
        Nucleus_deallocateMemory(pixelFormats);
        pixelFormats = NULL;
        fprintf(stderr, "wglChoosePixelFormatARB failed\n");
        status = Nucleus_Status_EnvironmentFailed;
        goto End;
    }
    for (UINT i = 0, n = actualNumberOfFormats; i < n; ++i)
    {
        Nucleus_Media_VideoSystemConfiguration *configuration;
        status = Nucleus_Media_VideoSystemConfiguration_create(&configuration);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_deallocateMemory(pixelFormats);
            pixelFormats = NULL;
            fprintf(stderr, "Nucleus_Media_VideoSystemConfiguration_create failed\n");
            status = Nucleus_Status_EnvironmentFailed;
            goto End;
        }
        status = getConfiguration(configuration, pixelFormats[i]);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_deallocateMemory(pixelFormats);
            pixelFormats = NULL;
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configuration));
            fprintf(stderr, "getConfiguration failed\n");
            status = Nucleus_Status_EnvironmentFailed;
            goto End;
        }
        status = Nucleus_ObjectArray_append(configurations, NUCLEUS_OBJECT(configuration));
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(configuration));
        if (Nucleus_Unlikely(status))
        {
            Nucleus_deallocateMemory(pixelFormats);
            pixelFormats = NULL;
            fprintf(stderr, "Nucleus_ObjectArray_append failed\n");
            status = Nucleus_Status_EnvironmentFailed;
            goto End;
        }
    }
End:
    if (window.hGLRC)
    {
        // Destroy WGL context.
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(window.hGLRC);
        window.hGLRC = NULL;
    }
    if (window.hDC)
    {
        // Destroy device context.
        ReleaseDC(window.hWnd, window.hDC);
        window.hDC = NULL;
    }
    if (window.hWnd)
    {
        // Destroy window.
        DestroyWindow(window.hWnd);
        window.hWnd = NULL;
    }
    if (window.wndclass)
    {
        // Unregister window class.
        UnregisterClassA(CLASSNAME, hInstance);
        window.wndclass = 0;
    }
    // Return success.
    return Nucleus_Status_Success;
}

#endif
