#ifndef PROPERTYGROUP_H
#define PROPERTYGROUP_H

#include <QList>

#include "property.h"

class PropertyGroup
{
public:
    PropertyGroup();

    QString         name() const;
    void            setName(const QString aName);

    QList<Property> properties() const;
    void            setProperties(const QList<Property> aProperties);

protected:
    QString         mName;
    QList<Property> mProperties;
};

#endif // PROPERTYGROUP_H
