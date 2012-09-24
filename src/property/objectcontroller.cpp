#include "objectcontroller.h"

#include <QVBoxLayout>

ObjectController::ObjectController(QWidget *parent) :
    QWidget(parent)
{
    mTreeWidget=new QTreeWidget(this);

    mTreeWidget->setColumnCount(2);
    mTreeWidget->setHeaderLabels(QStringList() << "Property" << "Value");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(mTreeWidget);

    setRootIsDecorated(false);
}

void ObjectController::invalidate()
{
    mTreeWidget->clear();
}

void ObjectController::reset()
{
    for (HandledObjects::iterator i=mHandledObjects.begin(); i!=mHandledObjects.end(); ++i)
    {
        i.value()->reset();
    }

    invalidate();
}

void ObjectController::clear()
{
    mTreeWidget->clear();
    mObjects.clear();

    while (mHandledObjects.count()>0)
    {
        HandledObjects::iterator first=mHandledObjects.begin();

        delete first.value();
        mHandledObjects.erase(first);
    }
}

void ObjectController::setObject(QObject *aObject)
{
    QObjectList aTempList;
    aTempList.append(aObject);
    setObjects(aTempList);
}

void ObjectController::setObjects(const QObjectList &aObjects)
{
    for (HandledObjects::iterator i=mHandledObjects.begin(); i!=mHandledObjects.end(); )
    {
        if (aObjects.contains(i.key()))
        {
            ++i;
        }
        else
        {
            HandledObjects::iterator it=i;
            ++i;

            delete it.value();
            mHandledObjects.erase(it);
        }
    }

    for (int i=0; i<aObjects.length(); ++i)
    {
        if (!mHandledObjects.contains(aObjects.at(i)))
        {
            mHandledObjects[aObjects.at(i)]=new HandleObject(this, aObjects.at(i));
        }
    }

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
