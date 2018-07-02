#include "Nucleus/Media/Plugin.h"

Nucleus_ClassTypeDefinition(Nucleus_Media_Library_Export,
                            "Nucleus.Media.Plugin",
                            Nucleus_Media_Plugin,
                            Nucleus_Object)

Nucleus_NonNull() static Nucleus_Status
equalTo
    (
        Nucleus_Media_Plugin *self,
        Nucleus_Media_Plugin *other,
        Nucleus_Boolean *equalTo
    )
{
    if (Nucleus_Unlikely(!self) || !other || !equalTo) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_String *selfName;
    status = Nucleus_Media_Plugin_getName(self, &selfName);
    if (Nucleus_Unlikely(status))
    {
        return status;
    }
    Nucleus_String *otherName;
    status = Nucleus_Media_Plugin_getName(self, &otherName);
    if (Nucleus_Unlikely(status))
    {
        Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(selfName));
        return status;
    }
    status = Nucleus_Object_equalTo(NUCLEUS_OBJECT(selfName), NUCLEUS_OBJECT(otherName), equalTo);
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(otherName));
    Nucleus_Object_decrementReferenceCount(NUCLEUS_OBJECT(selfName));
    return status;
}
                 
Nucleus_AlwaysSucceed() Nucleus_NonNull(1) static Nucleus_Status
destruct
    (
        Nucleus_Media_Plugin *self
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() static Nucleus_Status
constructDispatch
    (
        Nucleus_Media_Plugin_Class *dispatch
    )
{
    dispatch->getName = NULL;
    dispatch->startup = NULL;
    dispatch->shutdown = NULL;
    NUCLEUS_OBJECT_CLASS(dispatch)->equalTo = (Nucleus_Status (*)(Nucleus_Object *, Nucleus_Object *, Nucleus_Boolean *))&equalTo;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
constructSignals
    (
        Nucleus_Media_Plugin_Class *dispatch
    )
{ return Nucleus_Status_Success; }

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_construct
    (
        Nucleus_Media_Plugin *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    Nucleus_Type *type;
    Nucleus_Status status;
    status = Nucleus_Media_Plugin_getType(&type);
    if (Nucleus_Unlikely(status)) return status;
    status = Nucleus_Object_construct(NUCLEUS_OBJECT(self));
    if (Nucleus_Unlikely(status)) return status;
    NUCLEUS_OBJECT(self)->type = type;
    return Nucleus_Status_Success;        
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_getName
    (
        Nucleus_Media_Plugin *self,
        Nucleus_String **name
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    return getDispatch(self)->getName(self, name);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_startup
    (
        Nucleus_Media_Plugin *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    return getDispatch(self)->startup(self);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Media_Plugin_shutdown
    (
        Nucleus_Media_Plugin *self
    )
{
    if (Nucleus_Unlikely(!self)) return Nucleus_Status_InvalidArgument;
    return getDispatch(self)->shutdown(self);
}
