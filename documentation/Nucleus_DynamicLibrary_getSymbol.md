# `Nucleus_DynamicLibrary_getSymbol`

## C Signature
```
Nucleus_Status
Nucleus_DynamicLibrary_getSymbol
    (
        Nucleus_DynamicLibrary *dynamicLibrary,
        const char *symbolName,
        void **symbol
    )
```

## Parameters
- `dynamicLibrary`
- `symbolName`
- `symbol`

## Description

This function fails iff at least one of the following conditions is true:
- `dynamicLibrary`, `symbolName`, or `symbol` is a null pointer
- the dynamic library is not opened
- a symbol of the specified name was not found

The conditions are checked in the specified order and under the first case
`Nucleus_Status_InvalidArgument` is returned, under the second condition `Nucleus_Status_NotOpen` is
returned, and under the third condition `Nucleus_Status_NotFound` is returned.
