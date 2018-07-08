#include <Windows.h>
#include <xaudio2.h>

#include "Nucleus/Status.h"

Nucleus_Status initialize()
{
    //
    IXAudio2* pXAudio2 = NULL;
    HRESULT hr;
    if (FAILED(hr = XAudio2Create( &amp;pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
    { return Nucleus_Status_EnvironmentFailed; }
    return Nucleus_Status_Success;
}