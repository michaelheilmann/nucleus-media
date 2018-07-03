// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/OOP/Include.h"

Nucleus_ClassTypeDeclaration(Nucleus_Media_Library_Export,
                             "Nucleus.Media.VideoSystemConfiguration",
                             Nucleus_Media_VideoSystemConfiguration,
                             Nucleus_Object)
#define NUCLEUS_MEDIA_VIDEOSYSTEMCONFIGURATION(p) ((Nucleus_Media_VideoSystemConfiguration *)(p))
#define NUCLEUS_MEDIA_VIDEOSYSTEMCONFIGURATION_CLASS(p) ((Nucleus_Media_VideoSystemConfiguration_Class *)(p))

struct Nucleus_Media_VideoSystemConfiguration_Class
{
    Nucleus_Object_Class parent;
	Nucleus_Status (*compare)(const Nucleus_Media_VideoSystemConfiguration *self,
	                          const Nucleus_Object *other);
}; // struct Nucleus_Media_VideoSystemConfiguration_Class

struct Nucleus_Media_VideoSystemConfiguration
{
    Nucleus_Object parent;
	int numberOfSampleBuffers; /* Number of sample buffers. Default is 0. */
	int numberOfSamples; /* Number of samples. Default is 0. */
	int redBits, greenBits, blueBits, alphaBits; /* Red, green, blue, and alpha bits. Default is 8. */
	int depthBits; /* Depth bits. Default is 24. */
	int stencilBits; /* Stencil bits. Default is 8. */
}; // struct Nucleus_Media_VideoSystemConfiguration

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_construct
    (
        Nucleus_Media_VideoSystemConfiguration *self
    );

Nucleus_Media_Library_Export Nucleus_NonNull(1) Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_create
    (
        Nucleus_Media_VideoSystemConfiguration **videoSystemConfiguration
    );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getNumberOfSampleBuffers
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int *numberOfSampleBuffers
	);

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setNumberOfSampleBuffers
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int numberOfSampleBuffers
	);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getNumberOfSamples
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int *numberOfSamples
	);

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setNumberOfSamples
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int numberOfSamples
	);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getRedBits
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int *redBits
	);

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setRedBits
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int redBits
	);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getGreenBits
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int *greenBits
	);

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setGreenBits
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int greenBits
	);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getBlueBits
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int *blueBits
	);

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setBlueBits
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int blueBits
	);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getAlphaBits
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int *alphaBits
	);

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setAlphaBits
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int alphaBits
	);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getDepthBits
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int *depthBits
	);

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setDepthBits
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int depthBits
	);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_getStencilBits
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int *stencilBits
	);

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_VideoSystemConfiguration_setStencilBits
	(
		Nucleus_Media_VideoSystemConfiguration *self,
		int stencilBits
	);
