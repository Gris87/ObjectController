#include "property.h"

Property::Property(const QMetaProperty aProperty)
{
    mName=aProperty.name();
}

QString Property::name() const
{
    return mName;
}
