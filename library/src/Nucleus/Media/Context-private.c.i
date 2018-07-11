// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Media/Context-private.h.i"
#include "Nucleus/C/strcpy.h"
#include "Nucleus/C/strcat.h"

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
    C_strcpy(dynamicLibraryPathname, dynamicLibrarySearchPathPathname);
    C_strcat(dynamicLibraryPathname, dynamicLibraryFilename);
    C_strcat(dynamicLibraryPathname, ".");
    C_strcat(dynamicLibraryPathname, dllExtension);
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
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN)
    //
    status = loadDynamicallyLoadableLibrary(u8"Nucleus.Media.Plugin.OpenGL");
    if (status) { return status; }
    //
    status = loadDynamicallyLoadableLibrary(u8"Nucleus.Media.Plugin.OpenAL");
    if (status) { return status; }
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    //
    status = loadDynamicallyLoadableLibrary(u8"Nucleus.Media.Plugin.Metal");
    if (status) { return status; }
    //
    status = loadDynamicallyLoadableLibrary(u8"Nucleus.Media.Plugin.OpenAL");
    if (status) { return status; }
#else
    //
    #error(u8"environment not supported")
#endif
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_loadPluginLibraries
    (
        Nucleus_Media_Context *context
    )
{
    //
    if (Nucleus_Unlikely(!context)) return Nucleus_Status_InvalidArgument;
    //
    Nucleus_Status status;
    status = loadDynamicLoadableLibraries();
    if (Nucleus_Unlikely(status)) return status;
    //
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_registerPlugins
    (
        Nucleus_Media_Context *context
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
        status = Nucleus_Collections_PointerHashMap_set(&context->plugins,
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
Nucleus_Media_Context_startupPlugins
    (
        Nucleus_Media_Context *context
    )
{
    if (Nucleus_Unlikely(!context)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_Collections_PointerHashMap_ConstantEnumerator e;
    status = Nucleus_Collections_PointerHashMap_ConstantEnumerator_initialize(&e, &context->plugins);
    if (Nucleus_Unlikely(status)) return status;
    while (Nucleus_Boolean_True)
    {
        //
        Nucleus_Boolean hasValue;
        status = Nucleus_Collections_PointerHashMap_ConstantEnumerator_hasValue(&e, &hasValue);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&e);
            Nucleus_Media_Context_unregisterFactories(context);
            Nucleus_Media_Context_shutdownPlugins(context);
            return status;
        }
        if (!hasValue)
        {
            break;
        }
        //
        char *key;
        Nucleus_Media_Plugin *value;
        status = Nucleus_Collections_PointerHashMap_ConstantEnumerator_getValue(&e, (void **)&key,
                                                                                (void **)&value);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&e);
            Nucleus_Media_Context_unregisterFactories(context);
            Nucleus_Media_Context_shutdownPlugins(context);
            return status;
        }
        //
        status = Nucleus_Media_Plugin_startup(value);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&e);
            Nucleus_Media_Context_unregisterFactories(context);
            Nucleus_Media_Context_shutdownPlugins(context);
            return status;
        }
        //
        status = Nucleus_Collections_PointerHashMap_ConstantEnumerator_next(&e);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&e);
            Nucleus_Media_Context_unregisterFactories(context);
            Nucleus_Media_Context_shutdownPlugins(context);
            return status;
        }
    }
    Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&e);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_shutdownPlugins
    (
        Nucleus_Media_Context *context
    )
{
    if (Nucleus_Unlikely(!context)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_Collections_PointerHashMap_ConstantEnumerator e;
    status = Nucleus_Collections_PointerHashMap_ConstantEnumerator_initialize(&e, &context->plugins);
    if (Nucleus_Unlikely(status)) return status;
    while (Nucleus_Boolean_True)
    {
        //
        Nucleus_Boolean hasValue;
        status = Nucleus_Collections_PointerHashMap_ConstantEnumerator_hasValue(&e, &hasValue);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&e);
            return status;
        }
        if (!hasValue)
        {
            break;
        }
        //
        char *key;
        Nucleus_Media_Plugin *value;
        status = Nucleus_Collections_PointerHashMap_ConstantEnumerator_getValue(&e, (void **)&key,
                                                                                (void **)&value);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&e);
            return status;
        }
        //
        status = Nucleus_Media_Plugin_shutdown(value);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&e);
            return status;
        }
        //
        status = Nucleus_Collections_PointerHashMap_ConstantEnumerator_next(&e);
        if (Nucleus_Unlikely(status))
        {
            Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&e);
            Nucleus_Media_Context_shutdownPlugins(context);
            return status;
        }
    }
    Nucleus_Collections_PointerHashMap_ConstantEnumerator_uninitialize(&e);
    return Nucleus_Status_Success;
}

Nucleus_Media_Library_Export Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_unregisterFactories
    (
        Nucleus_Media_Context *context
    )
{
    Nucleus_ObjectArray_clear(context->audioSystemFactories);
    Nucleus_ObjectArray_clear(context->videoSystemFactories);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Context_unregisterPlugins
    (
        Nucleus_Media_Context *context
    )
{
    Nucleus_Collections_PointerHashMap_clear(&context->plugins);
    return Nucleus_Status_Success;
}
