# Nucleus: Object
Nucleus: Object is anextension to (Nucleus)[https://github.com/primordialmachine/nucleus)
provigin features like sub-typing, reference-counting, properties, and signals, as well
as dynamic loading of code ("runtime-time linkable libraries" as opposed to
"load-time linkable libraries" and "compile-time linkable libraries"). It also
defines concepts.

The following program initializes `Nucleus: Media` and uninitializes the Nucleus: Media
library.

```
#include "Nucleus/Media.h"

int main(int argc, char **argv)
{
    Nucleus_Status status;
    Nucleus_MediaContext *mediaContext;
    status = Nucleus_MediaContext_create(&mediaContext);
    if (status) return EXIT_FAILURE;
    Nucleus_ReferenceCountedOjbect_decrementReferenceCount(mediaContext);
    return EXIT_SUCCESS;
}
```

- Most functions return a `Nucleus_Status` status code value.
  A value of 

# Concepts
Concept is a term that describes a named set of requirements for a type.

- [ReferenceCountedObject](ReferenceCountedObject.md)
- [Enumerator](Enumerator.md)
- [EnumerableCollection](EnumerableCollection.md)