#include "propertygroup.h"

PropertyGroup::PropertyGroup()
{
}

QString PropertyGroup::name() const
{
    return mName;
}

void PropertyGroup::setName(const QString aName)
{
    mName=aName;
}

QList<Property> PropertyGroup::properties() const
{
    return mProperties;
}

void PropertyGroup::setProperties(const QList<Property> aProperties)
{
    mProperties=aProperties;
}
