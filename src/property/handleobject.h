#ifndef HANDLEOBJECT_H
#define HANDLEOBJECT_H

#include <QObject>

#include "propertygroup.h"

class ObjectController;

class HandleObject
{
public:
    HandleObject(ObjectController *aController, QObject *aObject);
    ~HandleObject();

    void reset();

    ObjectController*      controller() const;
    QObject*               object() const;
    QList<PropertyGroup *> classProperties() const;

protected:
    ObjectController      *mController;
    QObject               *mObject;
    QList<PropertyGroup *> mClassProperties;

    void clear();
};

#endif // HANDLEOBJECT_H
