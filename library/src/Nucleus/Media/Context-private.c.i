// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Media/Context-private.h.i"

Nucleus_NonNull() static Nucleus_Status
loadDynamicallyLoadableLibrary
    (
        const char *dynamicLibraryFilename
    )
{
    Nucleus_Status status;
    Nucleus_DynamicLibrary *dynamicLibrary;
    
    // Get the DLL search path.
    char *dynamicLibrarySearchPathPathname;
    status = Nucleus_getExecutableDirectoryPathname(&dynamicLibrarySearchPathPathname);
    if (status)
    {
        fprintf(stderr, "%s:%d: %s failed\n", __FILE__, __LINE__,
                        "Nucleus_getExecutableDirectoryPathname");
        return status;
    }

    // Concatenate DLL search path, DLL file name, '.', and DLL extension.
    char *dynamicLibraryPathname;
    status = Nucleus_allocateArrayMemory((void **)&dynamicLibraryPathname,
                                         strlen(dynamicLibrarySearchPathPathname) +
                                         strlen(dynamicLibraryFilename) + 
                                         strlen(".") + 
                                         strlen(dllExtension) + 1, sizeof(char));
    if (status)
    {
        fprintf(stderr, u8"%s:%d: %s failed\n", __FILE__, __LINE__,
                        u8"Nucleus_allocateMemory");
        Nucleus_deallocateMemory(dynamicLibrarySearchPathPathname);
        return status;
    }
    strcpy(dynamicLibraryPathname, dynamicLibrarySearchPathPathname);
    strcat(dynamicLibraryPathname, dynamicLibraryFilename);
    strcat(dynamicLibraryPathname, ".");
    strcat(dynamicLibraryPathname, dllExtension);
    Nucleus_deallocateMemory(dynamicLibrarySearchPathPathname);
    
    // Load the DLL.
    status = Nucleus_Types_loadDynamicLibrary(dynamicLibraryPathname,
                                              &dynamicLibrary);
    if (Nucleus_Unlikely(status))
    {
        fprintf(stderr, u8"%s: %d: unable to load dynamically loadable library '%s'\n", __FILE__, __LINE__,
                        dynamicLibraryPathname);
        Nucleus_deallocateMemory(dynamicLibraryPathname);
        return status;
    }
    Nucleus_deallocateMemory(dynamicLibraryPathname);
    Nucleus_DynamicLibrary_unlock(dynamicLibrary);
    return Nucleus_Status_Success;
}

static Nucleus_Status
loadDynamicLoadableLibraries
    (
    )
{
    Nucleus_Status status;
#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    //
    status = loadDynamicallyLoadableLibrary(u8"Nucleus.Media.Plugin.OpenGL");
    if (status) { return status; }
    //
    status = loadDynamicallyLoadableLibrary(u8"Nucleus.Media.Plugin.Direct3D");
    if (status) { return status; }
    //
    status = loadDynamicallyLoadableLibrary(u8"Nucleus.Media.Plugin.XAudio2");
    if (status) { return status; }
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    //
    status = loadDynamicallyLoadableLibrary(u8"Nucleus.Media.Plugin.OpenGL");
    if (status) { return status; }
    //
    status = loadDynamicallyLoadableLibrary(u8"Nucleus.Media.Plugin.OpenAL");
    if (status) { return status; }
#else
    //
    #error("environment not supported")
#endif
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
initialize
    (
        Nucleus_MediaContext *mediaContext
    )
{
    //
    if (Nucleus_Unlikely(!mediaContext))
    {
        return Nucleus_Status_InvalidArgument;
    }
    //
    Nucleus_Status status;
    //
    status = Nucleus_Types_initialize();
    if (Nucleus_Unlikely(status))
    {
        return status; 
    }
    // No video system or audio system selected.
    mediaContext->videoSystem = NULL;
    mediaContext->audioSystem = NULL;
    //
    //
    status = Nucleus_Collections_PointerHashMap_initialize(&mediaContext->plugins,
                                                           0,
                                                           NUCLEUS_LOCKFUNCTION(&Nucleus_Object_incrementReferenceCount),
                                                           NUCLEUS_UNLOCKFUNCTION(&Nucleus_Object_decrementReferenceCount),
                                                           NUCLEUS_HASHFUNCTION(&Nucleus_Object_hash),
                                                           NUCLEUS_EQUALTOFUNCTION(&Nucleus_Object_equalTo),
                                                           NUCLEUS_LOCKFUNCTION(&Nucleus_Object_incrementReferenceCount),
                                                           NUCLEUS_UNLOCKFUNCTION(&Nucleus_Object_decrementReferenceCount));
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Types_uninitialize();
        return status;
    }
    //
    status = Nucleus_ObjectArray_create(&mediaContext->videoSystemFactories);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Collections_PointerHashMap_uninitialize(&mediaContext->plugins);
        Nucleus_Types_uninitialize();
        return status;
    }
    //
    status = Nucleus_ObjectArray_create(&mediaContext->audioSystemFactories);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(mediaContext->videoSystemFactories));
        mediaContext->videoSystemFactories = NULL;
        Nucleus_Collections_PointerHashMap_uninitialize(&mediaContext->plugins);
        Nucleus_Types_uninitialize();
        return status;
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
uninitialize
    (
        Nucleus_MediaContext *mediaContext
    )
{
    //
    if (mediaContext->videoSystem)
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(mediaContext->videoSystem));
        mediaContext->videoSystem = NULL;
    }
    if (mediaContext->audioSystem)
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(mediaContext->audioSystem));
        mediaContext->audioSystem = NULL;
    }
    //
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(mediaContext->audioSystemFactories));
    mediaContext->audioSystemFactories = NULL;
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(mediaContext->videoSystemFactories));
    mediaContext->videoSystemFactories = NULL;
    //
    Nucleus_Collections_PointerHashMap_uninitialize(&mediaContext->plugins);
    //
    Nucleus_Types_uninitialize();
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
create
    (
        Nucleus_MediaContext **mediaContext
    )
{
    if (Nucleus_Unlikely(!mediaContext)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_MediaContext *temporary;
    status = Nucleus_allocateMemory((void **)&temporary, sizeof(Nucleus_MediaContext));
    if (Nucleus_Unlikely(status)) return status;
    status = initialize(temporary);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_deallocateMemory(temporary);
        return status;
    }
    *mediaContext = temporary;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
destroy
    (
        Nucleus_MediaContext *mediaContext
    )
{
    if (Nucleus_Unlikely(!mediaContext)) return Nucleus_Status_InvalidArgument;
    uninitialize(mediaContext);
    Nucleus_deallocateMemory(mediaContext);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_loadPluginLibraries
    (
        Nucleus_MediaContext *mediaContext
    )
{
    //
    if (Nucleus_Unlikely(!mediaContext)) return Nucleus_Status_InvalidArgument;
    //
    Nucleus_Status status;
    status = loadDynamicLoadableLibraries();
    if (Nucleus_Unlikely(status)) return status;
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_registerPlugins
    (
        Nucleus_MediaContext *mediaContext
    )
{
    Nucleus_Status status;
    Nucleus_Size i, n;
    status = Nucleus_Types_getNumberOfDynamicLibraries(&n);
    if (Nucleus_Unlikely(status)) return status;
    for (i = 0; i < n; ++i)
    {
        Nucleus_DynamicLibrary *dynamicLibrary;
        status = Nucleus_Types_getDynamicLibrary(i, &dynamicLibrary);
        if (Nucleus_Unlikely(status))
        {
            return status;
        }
        void *createPlugin;
        status = Nucleus_DynamicLibrary_getSymbol(dynamicLibrary, u8"createPlugin", &createPlugin);
        if (Nucleus_Unlikely(status))
        {
            return status;
        }
        Nucleus_Media_Plugin *plugin;
        status = (*((Nucleus_Status (*)(Nucleus_Media_Plugin **))createPlugin))(&plugin);
        if (Nucleus_Unlikely(status))
        {
            return status;
        }
        //
        Nucleus_String *pluginName;
        status = Nucleus_Media_Plugin_getName(plugin, &pluginName);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(plugin));
            return status;
        }
        status = Nucleus_Collections_PointerHashMap_set(&mediaContext->plugins,
                                                        pluginName,
                                                        plugin,
                                                        Nucleus_Boolean_False);
        if (Nucleus_Unlikely(status))
        {
            if (Nucleus_Status_Exists == status)
            {
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(pluginName));
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(plugin));
                fprintf(stderr, "%s: %d: plugin of name '%s' already exists\n", __FILE__, __LINE__,
                        pluginName->bytes);
                return Nucleus_Status_Success;
            }
            else
            {
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(pluginName));
                Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(plugin));
                return status;          
            }
        }
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(pluginName));
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(plugin));
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_startupPlugins
    (
        Nucleus_MediaContext *mediaContext
    )
{
    if (Nucleus_Unlikely(!mediaContext)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_Collections_PointerHashMap_Enumerator e;
    status = Nucleus_Collections_PointerHashMap_Enumerator_initialize(&e, &mediaContext->plugins);
    if (Nucleus_Unlikely(status)) return status;
    while (Nucleus_Boolean_True)
    {
        //
        Nucleus_Boolean hasValue;
        status = Nucleus_Collections_PointerHashMap_Enumerator_hasValue(&e, &hasValue);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_Enumerator_uninitialize(&e);
            Nucleus_MediaContext_unregisterFactories(mediaContext);
            Nucleus_MediaContext_shutdownPlugins(mediaContext);
            return status;
        }
        if (!hasValue)
        {
            break;
        }
        //
        char *key;
        Nucleus_Media_Plugin *value;
        status = Nucleus_Collections_PointerHashMap_Enumerator_getValue(&e, (void **)&key,
                                                                            (void **)&value);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_Enumerator_uninitialize(&e);
            Nucleus_MediaContext_unregisterFactories(mediaContext);
            Nucleus_MediaContext_shutdownPlugins(mediaContext);
            return status;
        }
        //
        status = Nucleus_Media_Plugin_startup(value);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_Enumerator_uninitialize(&e);
            Nucleus_MediaContext_unregisterFactories(mediaContext);
            Nucleus_MediaContext_shutdownPlugins(mediaContext);
            return status;
        }
        //
        status = Nucleus_Collections_PointerHashMap_Enumerator_next(&e);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_Enumerator_uninitialize(&e);
            Nucleus_MediaContext_unregisterFactories(mediaContext);
            Nucleus_MediaContext_shutdownPlugins(mediaContext);
            return status;
        }
    }
    Nucleus_Collections_PointerHashMap_Enumerator_uninitialize(&e);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_shutdownPlugins
    (
        Nucleus_MediaContext *mediaContext
    )
{
    if (Nucleus_Unlikely(!mediaContext)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_Collections_PointerHashMap_Enumerator e;
    status = Nucleus_Collections_PointerHashMap_Enumerator_initialize(&e, &mediaContext->plugins);
    if (Nucleus_Unlikely(status)) return status;
    while (Nucleus_Boolean_True)
    {
        //
        Nucleus_Boolean hasValue;
        status = Nucleus_Collections_PointerHashMap_Enumerator_hasValue(&e, &hasValue);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_Enumerator_uninitialize(&e);
            return status;
        }
        if (!hasValue)
        {
            break;
        }
        //
        char *key;
        Nucleus_Media_Plugin *value;
        status = Nucleus_Collections_PointerHashMap_Enumerator_getValue(&e, (void **)&key,
                                                                            (void **)&value);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_Enumerator_uninitialize(&e);
            return status;
        }
        //
        status = Nucleus_Media_Plugin_shutdown(value);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_Enumerator_uninitialize(&e);
            return status;
        }
        //
        status = Nucleus_Collections_PointerHashMap_Enumerator_next(&e);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_Enumerator_uninitialize(&e);
            Nucleus_MediaContext_shutdownPlugins(mediaContext);
            return status;
        }
    }
    Nucleus_Collections_PointerHashMap_Enumerator_uninitialize(&e);
    return Nucleus_Status_Success;
}

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_unregisterFactories
    (
        Nucleus_MediaContext *mediaContext
    )
{
    Nucleus_ObjectArray_clear(mediaContext->audioSystemFactories);
    Nucleus_ObjectArray_clear(mediaContext->videoSystemFactories);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_MediaContext_unregisterPlugins
    (
        Nucleus_MediaContext *mediaContext
    )
{
    Nucleus_Collections_PointerHashMap_clear(&mediaContext->plugins);
    return Nucleus_Status_Success;
}
