#ifndef PROPERTYGROUP_H
#define PROPERTYGROUP_H

#include <QMetaObject>

#include "property.h"

class PropertyGroup
{
    friend class HandleObject;
public:
    PropertyGroup(const QMetaObject *aMetaObject);

    void addProperty(Property *aNewProperty);

    QString           name() const;
    QList<Property *> properties() const;

protected:
    QString           mName;
    QList<Property *> mProperties;

    void clear();
};

#endif // PROPERTYGROUP_H
