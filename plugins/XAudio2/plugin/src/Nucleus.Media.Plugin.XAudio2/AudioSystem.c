#include "Nucleus.Media.Plugin.XAudio2/AudioSystem.h"

#include "Nucleus.Media.XAudio2Wrapper/XAudio2Wrapper.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_XAudio2_Export,
                            u8"Nucleus.Media.Plugin.XAudio2.AudioSystem",
                            Nucleus_Media_Plugin_XAudio2_AudioSystem,
                            Nucleus_Media_AudioSystem)

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystem_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystem_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystem *self
    )
{
    XAudio2Wrapper_uninitialize();
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_XAudio2_AudioSystem_construct
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystem *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_Plugin_XAudio2_AudioSystem_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Media_AudioSystem_construct(NUCLEUS_MEDIA_AUDIOSYSTEM(self));
    if (Nucleus_Unlikely(status)) return status;
    if (XAudio2Wrapper_initialize())
    {
        return Nucleus_Status_EnvironmentFailed;
    }
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineDefaultCreate(Nucleus_Media_Plugin_XAudio2_AudioSystem)
