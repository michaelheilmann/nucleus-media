// Copyright (c) 2018 Michael Heilmann
#include "Nucleus.Media.Plugin.XAudio2/AudioSystemFactory.h"
#include "Nucleus.Media.Plugin.XAudio2/AudioSystem.h"

#include "Nucleus.Media.Plugin.XAudio2/getAudioSystemConfigurations.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Plugin_XAudio2_Export,
                            u8"Nucleus.Media.Plugin.XAudio2.AudioSystemFactory",
                            Nucleus_Media_Plugin_XAudio2_AudioSystemFactory,
                            Nucleus_Media_AudioSystemFactory)


Nucleus_NonNull() static Nucleus_Status
getSystemName
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystemFactory *self,
        Nucleus_String **systemName
    );

Nucleus_NonNull() static Nucleus_Status
createSystem
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystemFactory *self,
        Nucleus_Media_AudioSystem **system
    );

Nucleus_NonNull() static Nucleus_Status
getConfigurations
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystemFactory *self,
        Nucleus_ObjectArray **configurations
    );

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystemFactory_Class *dispatch
    )
{
    NUCLEUS_MEDIA_AUDIOSYSTEMFACTORY_CLASS(dispatch)->createSystem = (Nucleus_Status(*)(Nucleus_Media_AudioSystemFactory *, Nucleus_Media_AudioSystem **))&createSystem;
    NUCLEUS_MEDIA_AUDIOSYSTEMFACTORY_CLASS(dispatch)->getSystemName = (Nucleus_Status(*)(Nucleus_Media_AudioSystemFactory *, Nucleus_String **))&getSystemName;
    NUCLEUS_MEDIA_AUDIOSYSTEMFACTORY_CLASS(dispatch)->getConfigurations = (Nucleus_Status(*)(Nucleus_Media_AudioSystemFactory *, Nucleus_ObjectArray **))&getConfigurations;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystemFactory_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull() static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystemFactory *self
    )
{
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(self->systemName));
    self->systemName = NULL;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
getSystemName
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystemFactory *self,
        Nucleus_String **systemName
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Object_incrementReferenceCount(NUCLEUS_OBJECT(self->systemName));
    *systemName = self->systemName;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
createSystem
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystemFactory *self,
        Nucleus_Media_AudioSystem **system
    )
{
    if (Nucleus_Unlikely(!self || !system)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Media_Plugin_XAudio2_AudioSystem_create((Nucleus_Media_Plugin_XAudio2_AudioSystem **)system);
}

Nucleus_NonNull() static Nucleus_Status
getConfigurations
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystemFactory *self,
        Nucleus_ObjectArray **configurations
    )
{
    if (Nucleus_Unlikely(!self || !configurations)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_ObjectArray *temporary;
    status = Nucleus_ObjectArray_create(&temporary);
    if (Nucleus_Unlikely(status))
    {
        return status;
    }
    //
    status = getAudioSystemConfigurations(temporary);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(temporary));
        return status;
    }
    //
    *configurations = temporary;
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_XAudio2_AudioSystemFactory_construct
    (
        Nucleus_Media_Plugin_XAudio2_AudioSystemFactory *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_Plugin_XAudio2_AudioSystemFactory_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Media_AudioSystemFactory_construct(NUCLEUS_MEDIA_AUDIOSYSTEMFACTORY(self));
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_String_create(&self->systemName, u8"XAudio2 Audio System");
    if (Nucleus_Unlikely(status)) return status;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

Nucleus_DefineDefaultCreate(Nucleus_Media_Plugin_XAudio2_AudioSystemFactory)
