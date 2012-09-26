#include "propertygroup.h"

PropertyGroup::PropertyGroup(const QMetaObject *aMetaObject, const QString &aName)
{
    mMetaObject=aMetaObject;
    mName=aName;
}

PropertyGroup::PropertyGroup(PropertyGroup *aPropertyGroup)
{
    mMetaObject = aPropertyGroup->mMetaObject;
    mName       = aPropertyGroup->mName;
    mProperties = aPropertyGroup->mProperties;
}

bool PropertyGroup::equals(const PropertyGroup *aPropertyGroup)
{
    return mMetaObject==aPropertyGroup->mMetaObject;
}

void PropertyGroup::addProperty(Property *aNewProperty)
{
    mProperties.append(aNewProperty);
}

void PropertyGroup::intersect(PropertyGroup *aPropertyGroup)
{
    for (int i=0; i<mProperties.length(); ++i)
    {
        bool good=false;

        for (int j=0; j<aPropertyGroup->mProperties.length(); ++j)
        {
            if (mProperties.at(i)->equals(aPropertyGroup->mProperties.at(j)))
            {
                good=true;
                break;
            }
        }

        if (!good)
        {
            // We are not deleting property object. Because this function is used to get CommonProperties only
            mProperties.removeAt(i);
            --i;
        }
    }
}

void PropertyGroup::clear()
{
    for (int i=0; i<mProperties.length(); ++i)
    {
        delete mProperties.at(i);
    }

    mProperties.clear();
}

// -------------------------------------------------------------------------------------

const QMetaObject* PropertyGroup::metaObject() const
{
    return mMetaObject;
}

QString PropertyGroup::name() const
{
    return mName;
}

QList<Property *> PropertyGroup::properties() const
{
    return mProperties;
}
