#ifndef PROPERTYGROUP_H
#define PROPERTYGROUP_H

#include <QMetaObject>

#include "property.h"

class PropertyGroup
{
    friend class HandleObject;
public:
    PropertyGroup(const QMetaObject *aMetaObject, const QString &aName);
    PropertyGroup(PropertyGroup *aPropertyGroup);

    bool equals(const PropertyGroup *aPropertyGroup);

    void addProperty(Property *aNewProperty);
    void intersect(PropertyGroup *aPropertyGroup);

    const QMetaObject* metaObject() const;
    QString            name() const;
    QList<Property *>  properties() const;

protected:
    const QMetaObject *mMetaObject;
    QString            mName;
    QList<Property *>  mProperties;

    void clear();
};

#endif // PROPERTYGROUP_H
