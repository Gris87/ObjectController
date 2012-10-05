#include "objectcontroller.h"

#include <QVBoxLayout>

#include "delegates/booldelegate.h"
#include "delegates/integerdelegate.h"
#include "delegates/doubledelegate.h"
#include "delegates/stringdelegate.h"
#include "delegates/chardelegate.h"

ObjectController::ObjectController(QWidget *parent) :
    QWidget(parent)
{
    mTreeWidget=new PropertyTreeWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(mTreeWidget);

    mTreeWidget->setRootIsDecorated(false);
}

void ObjectController::invalidate()
{
    if (mObjects.length()==0)
    {
        mTreeWidget->clear();
        return;
    }

    QList<PropertyGroup *> aCommonProperties;

    for (HandledObjects::const_iterator i=mHandledObjects.constBegin(); i!=mHandledObjects.constEnd(); ++i)
    {
        QList<PropertyGroup *> aClassProperties=i.value()->classProperties();

        if (i==mHandledObjects.constBegin())
        {
            for (int j=0; j<aClassProperties.length(); ++j)
            {
                aCommonProperties.append(new PropertyGroup(aClassProperties.at(j)));
            }
        }
        else
        {
            for (int j=0; j<aCommonProperties.length(); ++j)
            {
                bool good=false;

                for (int k=0; k<aClassProperties.length(); ++k)
                {
                    if (aCommonProperties.at(j)->equals(aClassProperties.at(k)))
                    {
                        aCommonProperties[j]->intersect(aClassProperties.at(k));
                        good=aCommonProperties.at(j)->properties().length()>0;
                        break;
                    }
                }

                if (!good)
                {
                    delete aCommonProperties.at(j);
                    aCommonProperties.removeAt(j);
                    --j;
                }
            }
        }
    }

    mTreeWidget->fillByPropertyGroups(aCommonProperties);

    for (int i=0; i<aCommonProperties.length(); ++i)
    {
        delete aCommonProperties.at(i);
    }

    update();
}

void ObjectController::update()
{
    mTreeWidget->update(mObjects);
}

void ObjectController::reset()
{
    for (HandledObjects::const_iterator i=mHandledObjects.constBegin(); i!=mHandledObjects.constEnd(); ++i)
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

void ObjectController::valueChangedSlot(const QVariant &aNewValue)
{
    ((Property *)sender())->write(mObjects, aNewValue);
    update();
}

// -------------------------------------------------------------------------------------

void ObjectController::setObject(QObject *aObject)
{
    QObjectList aTempList;

    if (aObject)
    {
        aTempList.append(aObject);
    }

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

// -------------------------------------------------------------------------------------

bool ObjectController::filterClass(QString &/*aClassName*/)
{
    return true;
}

bool ObjectController::filterProperty(const QMetaObject * /*aMetaObject*/, QString /*aMetaPropertyName*/)
{
    return true;
}

void ObjectController::propertyAdded(const QMetaObject * /*aMetaObject*/, Property * /*aProperty*/)
{
    // Nothing
}

CustomDelegate* ObjectController::createBoolDelegate()
{
    return new BoolDelegate(this);
}

CustomDelegate* ObjectController::createCharDelegate()
{
    return new CharDelegate(this);
}

CustomDelegate* ObjectController::createIntegerDelegate()
{
    return new IntegerDelegate(this);
}

CustomDelegate* ObjectController::createDoubleDelegate()
{
    return new DoubleDelegate(this);
}

CustomDelegate* ObjectController::createStringDelegate()
{
    return new StringDelegate(this);
}
