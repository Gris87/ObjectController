#include "property.h"

Property::Property(const QMetaProperty &aMetaProperty)
{
    mMetaProperty=aMetaProperty;

    mName=mMetaProperty.name();
}

QString Property::name() const
{
    return mName;
}

QColor Property::backgroundColor() const
{
    return mBackgroundColor;
}
