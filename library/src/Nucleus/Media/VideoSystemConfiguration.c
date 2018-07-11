// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Media/VideoSystemConfiguration.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            u8"Nucleus.Media.VideoSystemConfiguration",
                            Nucleus_Media_VideoSystemConfiguration,
                            Nucleus_Object)

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_VideoSystemConfiguration_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_VideoSystemConfiguration_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_AlwaysSucceed() Nucleus_NonNull(1) static Nucleus_Status
destruct
    (
        Nucleus_Media_VideoSystemConfiguration *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_construct
    (
        Nucleus_Media_VideoSystemConfiguration *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_VideoSystemConfiguration_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Object_construct(NUCLEUS_OBJECT(self));
    if (Nucleus_Unlikely(status)) return status;
    self->numberOfSampleBuffers = 0;
    self->numberOfSamples = 0;
    self->redBits = 8; self->greenBits = 8; self->blueBits = 8; self->alphaBits = 8;
    self->depthBits = 24;
    self->stencilBits = 8;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getNumberOfSampleBuffers
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int *numberOfSampleBuffers
    )
{
    if (Nucleus_Unlikely(!self || !numberOfSampleBuffers)) return Nucleus_Status_InvalidArgument;
    *numberOfSampleBuffers = self->numberOfSampleBuffers;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setNumberOfSampleBuffers
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int numberOfSampleBuffers
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    self->numberOfSampleBuffers = numberOfSampleBuffers;
    return Nucleus_Status_Success;
}

Nucleus_DefineDefaultCreate(Nucleus_Media_VideoSystemConfiguration)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getNumberOfSamples
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int *numberOfSamples
    )
{
    if (Nucleus_Unlikely(!self || !numberOfSamples)) return Nucleus_Status_InvalidArgument;
    *numberOfSamples = self->numberOfSamples;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setNumberOfSamples
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int numberOfSamples
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    self->numberOfSamples = numberOfSamples;
    return Nucleus_Status_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getRedBits
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int *redBits
    )
{
    if (Nucleus_Unlikely(!self || !redBits)) return Nucleus_Status_InvalidArgument;
    *redBits = self->redBits;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setRedBits
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int redBits
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    self->redBits = redBits;
    return Nucleus_Status_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getGreenBits
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int *greenBits
    )
{
    if (Nucleus_Unlikely(!self || !greenBits)) return Nucleus_Status_InvalidArgument;
    *greenBits = self->greenBits;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setGreenBits
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int greenBits
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    self->greenBits = greenBits;
    return Nucleus_Status_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getBlueBits
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int *blueBits
    )
{
    if (Nucleus_Unlikely(!self || !blueBits)) return Nucleus_Status_InvalidArgument;
    *blueBits = self->blueBits;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setBlueBits
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int blueBits
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    self->blueBits = blueBits;
    return Nucleus_Status_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getAlphaBits
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int *alphaBits
    )
{
    if (Nucleus_Unlikely(!self || !alphaBits)) return Nucleus_Status_InvalidArgument;
    *alphaBits = self->alphaBits;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setAlphaBits
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int alphaBits
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    self->alphaBits = alphaBits;
    return Nucleus_Status_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getDepthBits
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int *depthBits
    )
{
    if (Nucleus_Unlikely(!self || !depthBits)) return Nucleus_Status_InvalidArgument;
    *depthBits = self->depthBits;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setDepthBits
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int depthBits
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    self->depthBits = depthBits;
    return Nucleus_Status_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getStencilBits
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int *stencilBits
    )
{
    if (Nucleus_Unlikely(!self || !stencilBits)) return Nucleus_Status_InvalidArgument;
    *stencilBits = self->stencilBits;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setStencilBits
    (
        Nucleus_Media_VideoSystemConfiguration *self,
        int stencilBits
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    self->stencilBits = stencilBits;
    return Nucleus_Status_Success;
}
