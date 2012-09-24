#ifndef HANDLEOBJECT_H
#define HANDLEOBJECT_H

#include <QObject>

#include "propertygroup.h"

class ObjectController;

class HandleObject
{
public:
    HandleObject(ObjectController *aController, QObject *aObject);

    void reset();

protected:
    ObjectController    *mController;
    QObject             *mObject;
    QList<PropertyGroup> mClassProperties;
};

#endif // HANDLEOBJECT_H
