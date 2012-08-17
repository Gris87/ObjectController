#include "objectcontroller.h"

ObjectController::ObjectController(QWidget *parent) :
    QWidget(parent)
{
}

void ObjectController::clear()
{
    mObjects.clear();
}

void ObjectController::setObject(QObject *aObject)
{
    QObjectList aTempList;
    aTempList.append(aObject);
    setObjects(aTempList);
}

void ObjectController::setObjects(const QObjectList &aObjects)
{
    mObjects=aObjects;
}

QObjectList ObjectController::objects() const
{
    return mObjects;
}
