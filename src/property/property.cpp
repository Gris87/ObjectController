#include "property.h"

Property::Property(const QMetaProperty &aMetaProperty)
{
    mMetaProperty=aMetaProperty;

    mName=mMetaProperty.name();
}

bool Property::equals(const Property *aProperty)
{
    return mName==aProperty->mName;
}

QVariant Property::read(const QObjectList &aObjects)
{
    if (aObjects.length()==0)
    {
        return "";
    }

    QVariant res=mMetaProperty.read(aObjects.at(0));

    for (int i=1; i<aObjects.length(); ++i)
    {
        QVariant aOneValue=mMetaProperty.read(aObjects.at(i));

        if (res!=aOneValue)
        {
            return "";
        }
    }

    return res;
}

void Property::write(const QObjectList &aObjects, const QVariant &aValue)
{
    for (int i=0; i<aObjects.length(); ++i)
    {
        mMetaProperty.write(aObjects[i], aValue);
    }
}

QString Property::name() const
{
    return mName;
}

QColor Property::backgroundColor() const
{
    return mBackgroundColor;
}
