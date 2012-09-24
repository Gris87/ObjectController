#include "handleobject.h"

#include <QStack>
#include <QMetaProperty>

#include "objectcontroller.h"

HandleObject::HandleObject(ObjectController *aController, QObject *aObject)
{
    mController=aController;
    mObject=aObject;

    reset();
}

void HandleObject::reset()
{
    QStack<const QMetaObject *> aMetaObjects;

    const QMetaObject *aMetaObject=mObject->metaObject();

    while (aMetaObject)
    {
        aMetaObjects.push(aMetaObject);
        aMetaObject=aMetaObject->superClass();
    }

    while (!aMetaObjects.isEmpty())
    {
        aMetaObject=aMetaObjects.pop();

        for (int j=aMetaObject->propertyOffset(); j<aMetaObject->propertyCount(); ++j)
        {
            QMetaProperty aProperty=aMetaObject->property(j);
        }
    }
}
