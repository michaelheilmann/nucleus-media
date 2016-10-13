// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/Context.h"
#include "Nucleus/Memory.h"
#include "Nucleus/Media/OOP/Include.h"
#include "Nucleus/Media/Plugin.h"
#include "Nucleus/Collections/PointerHashMap.h"
#include "Nucleus/Collections/PointerArray.h"
#include "Nucleus/Hash/Memory.h"
#include "Nucleus/getExecutableDirectoryPathname.h"
#include "Nucleus/Media/VideoSystem.h"
#include "Nucleus/Media/AudioSystem.h"
#include <string.h>
#include <stdio.h>

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)
    static const char *dllExtension = "dll";
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX) || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    static const char *dllExtension = "so";
#else
    #error("operating system not supported")
#endif

struct Nucleus_MediaContext
{
    Nucleus_DynamicLibraryManager *dynamicLibraryManager;
    Nucleus_Collections_PointerHashMap plugins;
    // List of video system factories.
    Nucleus_Collections_PointerArray videoSystemFactories;
    // List of audio system factories.
    Nucleus_Collections_PointerArray audioSystemFactories;
    // null or selected video system.
    Nucleus_Media_VideoSystem *videoSystem;
    // null or selected audio system.
    Nucleus_Media_AudioSystem *audioSystem;
}; // struct Nucleus_MediaContext

static Nucleus_MediaContext *g_singleton = NULL;
 
// Private to Nucleus_MediaContext extension to Nucleus_DynamicLibraryManager.
Nucleus_NonNull() static Nucleus_Status
loadDynamicallyLoadableLibrary
    (
        Nucleus_DynamicLibraryManager *dynamicLibraryManager,
        const char *dynamicLibraryName
    );
    
// Private to Nucleus_MediaContext extension to Nucleus_DynamicLibraryManager.
Nucleus_NonNull() static Nucleus_Status
loadDynamicLoadableLibraries
    (
        Nucleus_DynamicLibraryManager *dynamicLibraryManager
    );

Nucleus_NonNull() static Nucleus_Status
unloadDynamicLoadableLibraries
    (
        Nucleus_DynamicLibraryManager *dynamicLibraryManager
    );

// Private to Nucleus_MediaContext extension to Nucleus_PluginManager.

Nucleus_NonNull() static Nucleus_Status
initialize
    (
        Nucleus_MediaContext *mediaContext
    );

Nucleus_NonNull() static Nucleus_Status
uninitialize
    (
        Nucleus_MediaContext *mediaContext
    );

Nucleus_NonNull() static Nucleus_Status
create
    (
        Nucleus_MediaContext **mediaContext
    );

Nucleus_NonNull() static Nucleus_Status
destroy
    (
        Nucleus_MediaContext *mediaContext
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_unregisterFactories
    (
        Nucleus_MediaContext *mediaContext
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_startupPlugins
    (
        Nucleus_MediaContext *mediaContext
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_shutdownPlugins
    (
        Nucleus_MediaContext *mediaContext
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_startupPlugins
    (
        Nucleus_MediaContext *mediaContext
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_shutdownPlugins
    (
        Nucleus_MediaContext *mediaContext
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_registerPlugins
    (
        Nucleus_MediaContext *mediaContext
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_unregisterPlugins
    (
        Nucleus_MediaContext *mediaContext
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_loadPluginLibraries
    (
        Nucleus_MediaContext *mediaContext
    );

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_unloadPluginLibraries
    (
        Nucleus_MediaContext *mediaContext
    );
