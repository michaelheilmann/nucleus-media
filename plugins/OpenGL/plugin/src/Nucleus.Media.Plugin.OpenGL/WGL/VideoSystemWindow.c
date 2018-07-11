// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.OpenGL/WGL/VideoSystemWindow.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_OpenGL_Export,
                            u8"Nucleus.Media.Plugin.OpenGL.WGL.VideoSystemWindow",
                            Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow,
                            Nucleus_Media_Plugin_OpenGL_VideoSystemWindow)
    
Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow *self
    )
{
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(self->videoSystem));
    self->videoSystem = NULL;
    return Nucleus_Status_Success;
}

static LRESULT CALLBACK
WindowProcedure
    (
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    )
{
    switch (message)
    {
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;       // message handled
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow_construct
    (
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow *self,
        Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem *videoSystem
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Media_Plugin_OpenGL_VideoSystemWindow_construct(NUCLEUS_MEDIA_PLUGIN_OPENGL_VIDEOSYSTEMWINDOW(self));
    if (Nucleus_Unlikely(status)) return status;
    self->videoSystem = videoSystem;
    Nucleus_Object_incrementReferenceCount(NUCLEUS_OBJECT(videoSystem));
    //
    static const LPCSTR TITLE = "Nucleus: Media - Plugin: Direct3D 12 Window";
    static const LPCSTR CLASSNAME = "Nucleus.Media.Plugin.Direct3D.12.Window";
    // Get the module handle.
    self->hInstance = GetModuleHandle(NULL);
    // Configure the window class.
    WNDCLASSEXA wndclassex;
    ZeroMemory(&wndclassex, sizeof(wndclassex));
    wndclassex.cbSize = sizeof(wndclassex);
    wndclassex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclassex.hInstance = self->hInstance;
    wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclassex.lpfnWndProc = &WindowProcedure;
    wndclassex.lpszClassName = CLASSNAME;
    self->hWnd = NULL;
    self->wndclass = 0;
    // Register window class.
    self->wndclass = RegisterClassExA(&wndclassex);
    if (!self->wndclass)
    {
        fprintf(stderr, "unable to register window class\n");
        return Nucleus_Status_EnvironmentFailed;
    }
    // Create window.
    self->hWnd = CreateWindowA(CLASSNAME, // (1) Window class name.
        TITLE, // (2) Window title.
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // (3) Window style.
        0, 0, // (4), (5) Left and top position.
        1, 1, // (6), (7) Width and height.
        NULL, // (8) Parent window handle.
        NULL, // (9) Menu handle.
        self->hInstance, // (10) Module handle.
        NULL); // (11) Creation parameters.
    if (!self->hWnd)
    {
        fprintf(stderr, "unable to create window\n");
        UnregisterClassA(CLASSNAME, self->hInstance);
        self->wndclass = 0;
        return Nucleus_Status_EnvironmentFailed;
    }
    //
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineCreate(Nucleus_Media_Plugin_OpenGL_WGL_VideoSystemWindow,
                     Nucleus_Media_Plugin_OpenGL_WGL_VideoSystem *videoSystem,
                     videoSystem)

#endif
