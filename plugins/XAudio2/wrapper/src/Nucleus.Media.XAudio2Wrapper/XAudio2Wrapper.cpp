#include "Nucleus.Media.XAudio2Wrapper/XAudio2Wrapper.h"

#include <Windows.h>
#include <xaudio2.h>

static IXAudio2 *g_xaudio2 = NULL;

extern "C" Nucleus_Status
XAudio2Wrapper_initialize
    (
    )
{
    HRESULT hr;
    if (FAILED(hr = XAudio2Create(&g_xaudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
    { return Nucleus_Status_EnvironmentFailed; }
    return Nucleus_Status_Success;
}

extern "C" void
XAudio2Wrapper_uninitialize
    (
    )
{
    g_xaudio2->Release();
    g_xaudio2 = NULL;        
}
