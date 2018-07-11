// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Media/Context.h"
#include "Nucleus/Memory.h"
#include "Nucleus/Media/OOP/Include.h"
#include "Nucleus/Media/Plugin.h"
#include "Nucleus/Collections/PointerHashMap.h"
#include "Nucleus/Object/ObjectArray.h"
#include "Nucleus/Hash/Memory.h"
#include "Nucleus/getExecutableDirectoryPathname.h"
#include "Nucleus/Media/VideoSystemFactory.h"
#include "Nucleus/Media/AudioSystemFactory.h"
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

// Private to Nucleus_Media_Context extension to Nucleus_DynamicLibraryManager.
Nucleus_NonNull() static Nucleus_Status
loadDynamicallyLoadableLibrary
    (
        const char *dynamicLibraryName
    );

static Nucleus_Status
loadDynamicLoadableLibraries
    (
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_unregisterFactories
    (
        Nucleus_Media_Context *context
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_startupPlugins
    (
        Nucleus_Media_Context *context
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_shutdownPlugins
    (
        Nucleus_Media_Context *context
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_startupPlugins
    (
        Nucleus_Media_Context *context
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_shutdownPlugins
    (
        Nucleus_Media_Context *context
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_registerPlugins
    (
        Nucleus_Media_Context *context
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_unregisterPlugins
    (
        Nucleus_Media_Context *context
    );

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_loadPluginLibraries
    (
        Nucleus_Media_Context *context
    );
