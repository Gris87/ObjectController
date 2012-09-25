#include "propertygroup.h"

PropertyGroup::PropertyGroup(const QMetaObject *aMetaObject, const QString &aName)
{
    mName=aName;
}

void PropertyGroup::addProperty(Property *aNewProperty)
{
    mProperties.append(aNewProperty);
}

void PropertyGroup::clear()
{
    for (int i=0; i<mProperties.length(); ++i)
    {
        delete mProperties.at(i);
    }

    mProperties.clear();
}

QString PropertyGroup::name() const
{
    return mName;
}

QList<Property *> PropertyGroup::properties() const
{
    return mProperties;
}
