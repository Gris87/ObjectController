#ifndef PROPERTYGROUP_H
#define PROPERTYGROUP_H

#include <QMetaObject>
#include <QString>
#include <QList>

#include "property.h"

class PropertyGroup
{
public:
    PropertyGroup(const QMetaObject *aMetaObject);
    ~PropertyGroup();

    void addProperty(Property *aNewProperty);

    QString           name() const;
    QList<Property *> properties() const;

protected:
    QString           mName;
    QList<Property *> mProperties;

    void clear();
};

#endif // PROPERTYGROUP_H
