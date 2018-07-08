# Building under Windows 10/Cygwin/GCC
Make sure you to install the required packages via the Cygwin installer to have full GLX/OpenGL 3.1
and OpenAL support.

## OpenAL and PulseAudio
OpenAL requires an audio backend to work with. We recommend under Cygwin to use PulseAudio.
Install PulseAudio through your Cygwin installer. To test PulseAudio ensure to have a wave
file at your disposal. In this example, we use `/cygdrive/c/Windows/Media/tada.wav``. You
should hear the sound when entering `paplay /cygdrive/c/Windows/Media/tada.wav`.

## Building Nucleus: Media
Follow the build instructions linked below.

**The following build instructions and build options pertain to all products from the Nucleus series.
  All products accept the build options described here.
  The description of additional build options specific to a product are described in its documentation.
  The name of this product in the build system is `Nucleus.Media`.*

[Windows 10/Cygwin/GCC](https://github.com/primordialmachine/nucleus/blob/master/documentation/building-under-windows-10-cygwin-gcc.md)
