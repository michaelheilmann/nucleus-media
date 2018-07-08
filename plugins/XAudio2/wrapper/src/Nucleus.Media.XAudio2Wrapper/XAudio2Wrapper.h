#pragma once

#if __cplusplus
extern "C"
{
#endif
    #include "Nucleus/Status.h"
#if __cplusplus
}
#endif

// @brief Initialize XAudio2.
// @warning If XAudio2 is already initialized, the behavior of this function is undefined.
// @a 0 if XAudio2 was initialized, a non-zero value otherwise
#if __cplusplus
extern "C"
#endif
int
XAudio2Wrapper_initialize
    (
    );

// @brief Uninitialize XAudio2.
// @warning If XAudio2 is not initialized, the behavior of this function is undefined.
#if __cplusplus
extern "C"
#endif
void
XAudio2Wrapper_uninitialize
    (
    );
