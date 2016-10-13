# `Nucleus_MousePointerEvent_create`
*Create a `Nucleus_MousePointerEvent` object representing an event related to a mouse pointer.`

## C Signature
```
Nucleus_Status
Nucleus_MousePointerEvent_create
    (
        Nucleus_MousePointerEvent **event,
        Nucleus_MousePointerEventKinds kind,
        int x, int y
    )
```

## Parameters

## Description
This function creates a `Nucleus_MousePointerEvent` object.
These objects represent events related to a mouse pointer.

If this function success, `*event` is assigned the address of a `Nucleus_MousePointerEvent` object and `Nucleus_Status_Success` is returned.
This function fails iff `event` is a null pointer or an allocation failed.
In the former case `Nucleus_Status_InvalidArgument` is returned,
in the latter case `Nucleus_Status_AllocationFailed` is returned.

# `Nucleus_PointerEventKinds`
*An enumeration of the kinds of mouse pointer events.*

The `Nucleus_PointerEventKinds` enumeration contains the following members.
- `Nucleus_PointerEventKinds_Move`
- `Nucleus_PointerEventKinds_Enter`
- `Nucleus_PointerEventKinds_Leave`