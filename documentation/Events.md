# Event System
Events derive from the abstract class [Nucleus_Event](Nucleus_Event).

There are currently four categories of events: application events, window events, and input events.

## Application Events
Application events are represented by objects of the types [Nucleus_ApplicationEvent](Nucleus_ApplicationEvent.md).
Objects of the type `Nucleus_ApplicationEvent` (derived from `Nucleus_Event`) are created by calls to [Nucleus_ApplicationEvent_create](Nucleus_ApplicationEvent_create.md)

## Window Events

## Input Events
Input events are represented by objects of the types
[Nucleus_MouseButtonEvent](Nucleus_MouseButtonEvent.md),
[Nucleus_MousePointerEvent](Nucleus_MousePointerEvent.md), and
[Nucleus_KeyboardKeyEvent](Nucleus_KeyboardKeyEvent.md).

The first type of objects represent events pertaining to the (change of the state of) the buttons of a mouse,
the second type of objects represent events pertaining to the (change of the state of) the keys of a keyboard,
the third type of objects represent event pertaining to the position and motion of a mouse pointer.

### Keyboard Key Events
Objects of the type `Nucleus_KeyboardKeyEvent` (derived from `Nucleus_Event`) represent events related to the state of a keyboard key.
Objects of the type `Nucleus_KeyboardKeyEvent` are created by calls to [Nucleus_KeyboardKeyEvent_create](Nucleus_KeyboardKeyEvent_create.md).

### Mouse Button Events
Objects of the type `Nucleus_MouseButtonEvent` (derived from `Nucleus_Event`) represent events related to the state of a mouse button.
Objects of the type `Nucleus_MouseButtonEvent` are created by calls to [Nucleus_MouseButtonEvent_create](Nucleus_MouseButtonEvent_create.md).

### Mouse Pointer Events
Objects of the type `Nucleus_MousePointerEvent` (derived from `Nucleus_Event`) represent events related to the position and motion
of the mouse pointers as well as the relation of the mouse pointer to elements.
Objects of the type `Nucleus_MousePointerEvent` are created by calls to [Nucleus_MousePointerEvent_create](Nucleus_MousePointerEvent_create.md).
