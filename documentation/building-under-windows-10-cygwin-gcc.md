# Building under Windows 10/Cygwin/GCC
To compile and run Nucleus: Media-based software, the required dependencies need to be install.

#### OpenAL
To have OpenAL support under Cygwin, install the following packages:
- `libopenal-devel: Cross-platform 3D audio library`
- `libopenal1: Cross-platform 3D audio library`
- `openal-config: Cross-platform 3D audio library configuration GUI` (most likely not necessary)

OpenAL requires an audio backend to work with. We recommend under Cygwin to use PulseAudio.
Install `pulseaudio: PulseAudio sound server` and `pulseaudio-utils: PulseAudio sound server`
through your Cygwin installer. To test PulseAudio ensure to have a wave file at your disposal.
In this example, we use `/cygdrive/c/Windows/Media/tada.wav``. You should hear the sound when
entering `paplay /cygdrive/c/Windows/Media/tada.wav`.

#### OpenGL 3.1/GLX
First, install Cygwin/X as described [here](https://x.cygwin.com/docs/ug/setup.html#setup-cygwin-x-installing).
Second, install `libX11-devel: X.Org X11 core library (development)` and 
                `libGL-devel: X11 OpenGL library (development)`.
Third - and this might be important - , update your Windows graphics card drivers: For example, the
update was necessary on Samsung Notebook with an Intel HD 4000 graphics  card for OpenGL 3 support. 


The recommended way to test your systems OpenGL capabilities are the programs `glxgears` and `glxinfo`.

Open the terminal and enter
```
startxwin -- +iglx -nowgl
```
Open another terminal and enter
```
export LIBGL_ALWAYS_INDIRECT=1
glxgears
```
The `glxgears` window should display animated gears.

## Building Nucleus: Media
Follow the build instructions linked below.

**The following build instructions and build options pertain to all products from the Nucleus series.
  All products accept the build options described here.
  The description of additional build options specific to a product are described in its documentation.
  The name of this product in the build system is `Nucleus.Media`.*

[Windows 10/Cygwin/GCC](https://github.com/primordialmachine/nucleus/blob/master/documentation/building-under-windows-10-cygwin-gcc.md)
