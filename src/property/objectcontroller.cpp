#include "objectcontroller.h"

#include <QVBoxLayout>

#include "delegates/delegates.h"

ObjectController::ObjectController(QWidget *parent) :
    QWidget(parent)
{
    mIgnoreEmptyClass=true;

    mTreeWidget=new PropertyTreeWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(mTreeWidget);

    mTreeWidget->setRootIsDecorated(false);

    connect(mTreeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(currentItemChangedSlot(QTreeWidgetItem*,QTreeWidgetItem*)));
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
    emit valueChanged((Property *)sender(), aNewValue);
}

void ObjectController::currentItemChangedSlot(QTreeWidgetItem *aCurrent, QTreeWidgetItem * /*aPrevious*/)
{
    emit currentItemChanged((PropertyTreeWidgetItem *)aCurrent);
}

// -------------------------------------------------------------------------------------

void ObjectController::setIgnoreEmptyClass(bool aValue)
{
    if (mIgnoreEmptyClass!=aValue)
    {
        mIgnoreEmptyClass=aValue;
        invalidate();
    }
}

bool ObjectController::ignoreEmptyClass() const
{
    return mIgnoreEmptyClass;
}

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

void ObjectController::propertyAdded(Property * /*aProperty*/, const QMetaObject * /*aMetaObject*/, QString /*aMetaPropertyName*/)
{
    // Nothing
}

CustomDelegate* ObjectController::createEnumDelegate()
{
    return new EnumDelegate(this);
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

CustomDelegate* ObjectController::createSizePolicyDelegate()
{
    return new SizePolicyDelegate(this);
}

CustomDelegate* ObjectController::createKeySequenceDelegate()
{
    return new KeySequenceDelegate(this);
}

CustomDelegate* ObjectController::createPenDelegate()
{
    return new PenDelegate(this);
}

CustomDelegate* ObjectController::createTextLengthDelegate()
{
    return new TextLengthDelegate(this);
}

CustomDelegate* ObjectController::createTextFormatDelegate()
{
    return new TextFormatDelegate(this);
}

CustomDelegate* ObjectController::createMatrixDelegate()
{
    return new MatrixDelegate(this);
}

CustomDelegate* ObjectController::createTransformDelegate()
{
    return new TransformDelegate(this);
}

CustomDelegate* ObjectController::createMatrix4x4Delegate()
{
    return new Matrix4x4Delegate(this);
}

CustomDelegate* ObjectController::createVector2DDelegate()
{
    return new Vector2DDelegate(this);
}

CustomDelegate* ObjectController::createVector3DDelegate()
{
    return new Vector3DDelegate(this);
}

CustomDelegate* ObjectController::createVector4DDelegate()
{
    return new Vector4DDelegate(this);
}

CustomDelegate* ObjectController::createQuaternionDelegate()
{
    return new QuaternionDelegate(this);
}

