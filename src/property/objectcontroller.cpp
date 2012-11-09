#include "objectcontroller.h"

#include <QVBoxLayout>

#include "delegates/booldelegate.h"
#include "delegates/integerdelegate.h"
#include "delegates/doubledelegate.h"
#include "delegates/chardelegate.h"
#include "delegates/stringlistdelegate.h"
#include "delegates/stringdelegate.h"
#include "delegates/bytearraydelegate.h"
#include "delegates/bitarraydelegate.h"
#include "delegates/datedelegate.h"
#include "delegates/timedelegate.h"
#include "delegates/datetimedelegate.h"
#include "delegates/localedelegate.h"
#include "delegates/rectdelegate.h"
#include "delegates/rectfdelegate.h"
#include "delegates/sizedelegate.h"
#include "delegates/sizefdelegate.h"
#include "delegates/linedelegate.h"
#include "delegates/linefdelegate.h"
#include "delegates/pointdelegate.h"
#include "delegates/pointfdelegate.h"
#include "delegates/easingcurvedelegate.h"
#include "delegates/fontdelegate.h"
#include "delegates/pixmapdelegate.h"
#include "delegates/brushdelegate.h"
#include "delegates/colordelegate.h"
#include "delegates/palettedelegate.h"
#include "delegates/icondelegate.h"
#include "delegates/polygondelegate.h"
#include "delegates/regiondelegate.h"
#include "delegates/cursordelegate.h"

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

CustomDelegate* ObjectController::createIntegerDelegate()
{
    return new IntegerDelegate(this);
}

CustomDelegate* ObjectController::createDoubleDelegate()
{
    return new DoubleDelegate(this);
}

CustomDelegate* ObjectController::createCharDelegate()
{
    return new CharDelegate(this);
}

CustomDelegate* ObjectController::createStringListDelegate()
{
    return new StringListDelegate(this);
}

CustomDelegate* ObjectController::createStringDelegate()
{
    return new StringDelegate(this);
}

CustomDelegate* ObjectController::createByteArrayDelegate()
{
    return new ByteArrayDelegate(this);
}

CustomDelegate* ObjectController::createBitArrayDelegate()
{
    return new BitArrayDelegate(this);
}

CustomDelegate* ObjectController::createDateDelegate()
{
    return new DateDelegate(this);
}

CustomDelegate* ObjectController::createTimeDelegate()
{
    return new TimeDelegate(this);
}

CustomDelegate* ObjectController::createDateTimeDelegate()
{
    return new DateTimeDelegate(this);
}

CustomDelegate* ObjectController::createLocaleDelegate()
{
    return new LocaleDelegate(this);
}

CustomDelegate* ObjectController::createRectDelegate()
{
    return new RectDelegate(this);
}

CustomDelegate* ObjectController::createRectFDelegate()
{
    return new RectFDelegate(this);
}

CustomDelegate* ObjectController::createSizeDelegate()
{
    return new SizeDelegate(this);
}

CustomDelegate* ObjectController::createSizeFDelegate()
{
    return new SizeFDelegate(this);
}

CustomDelegate* ObjectController::createLineDelegate()
{
    return new LineDelegate(this);
}

CustomDelegate* ObjectController::createLineFDelegate()
{
    return new LineFDelegate(this);
}

CustomDelegate* ObjectController::createPointDelegate()
{
    return new PointDelegate(this);
}

CustomDelegate* ObjectController::createPointFDelegate()
{
    return new PointFDelegate(this);
}

CustomDelegate* ObjectController::createEasingCurveDelegate()
{
    return new EasingCurveDelegate(this);
}

CustomDelegate* ObjectController::createFontDelegate()
{
    return new FontDelegate(this);
}

CustomDelegate* ObjectController::createPixmapDelegate()
{
    return new PixmapDelegate(this);
}

CustomDelegate* ObjectController::createBrushDelegate()
{
    return new BrushDelegate(this);
}

CustomDelegate* ObjectController::createColorDelegate()
{
    return new ColorDelegate(this);
}

CustomDelegate* ObjectController::createPaletteDelegate()
{
    return new PaletteDelegate(this);
}

CustomDelegate* ObjectController::createIconDelegate()
{
    return new IconDelegate(this);
}

CustomDelegate* ObjectController::createPolygonDelegate()
{
    return new PolygonDelegate(this);
}

CustomDelegate* ObjectController::createRegionDelegate()
{
    return new RegionDelegate(this);
}

CustomDelegate* ObjectController::createCursorDelegate()
{
    return new CursorDelegate(this);
}
