#include "objectcontroller.h"

ObjectController::ObjectController(QWidget *parent) :
    QWidget(parent)
{
    mTreeWidget=new QTreeWidget(this);

    mTreeWidget->setColumnCount(2);
    mTreeWidget->setHeaderLabels(QStringList() << "Property" << "Value");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mTreeWidget);



    setRootIsDecorated(false);
}

void ObjectController::invalidate()
{
    mTreeWidget->clear();

    for (int i=0; i<mObjects.length(); ++i)
    {
        QStack<const QMetaObject *> aMetaObjects;

        const QMetaObject *aMetaObject=mObjects.at(i)->metaObject();

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
}

void ObjectController::clear()
{
    mObjects.clear();
    mTreeWidget->clear();
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
    invalidate();
}

QObjectList ObjectController::objects() const
{
    return mObjects;
}

void ObjectController::setRootIsDecorated(bool aDecorated)
{
    mTreeWidget->setRootIsDecorated(aDecorated);
}

bool ObjectController::rootIsDecorated()
{
    return mTreeWidget->rootIsDecorated();
}
