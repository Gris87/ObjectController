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

HandleObject::~HandleObject()
{
    clear();
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

    clear();

    while (!aMetaObjects.isEmpty())
    {
        aMetaObject=aMetaObjects.pop();

        QString aClassName=aMetaObject->className();

        if (!mController->filterClass(aClassName))
        {
            continue;
        }

        PropertyGroup *aPropertyGroup=new PropertyGroup(aMetaObject, aClassName);

        mClassProperties.append(aPropertyGroup);

        for (int j=aMetaObject->propertyOffset(); j<aMetaObject->propertyCount(); ++j)
        {
            QMetaProperty aProperty=aMetaObject->property(j);

            if (
                !aProperty.isReadable()
                ||
                !mController->filterProperty(aMetaObject, aProperty.name())
               )
            {
                continue;
            }

            aPropertyGroup->addProperty(new Property(aProperty, mController));
        }
    }
}

void HandleObject::clear()
{
    for (int i=0; i<mClassProperties.length(); ++i)
    {
        mClassProperties.at(i)->clear();
        delete mClassProperties.at(i);
    }

    mClassProperties.clear();
}

// -------------------------------------------------------------------------------------

ObjectController* HandleObject::controller() const
{
    return mController;
}

QObject* HandleObject::object() const
{
    return mObject;
}

QList<PropertyGroup *> HandleObject::classProperties() const
{
    return mClassProperties;
}
