#include "propertytreewidgetitem.h"

PropertyTreeWidgetItem::PropertyTreeWidgetItem(int type) : QTreeWidgetItem(type)
{
    init();
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(const QStringList &strings, int type) : QTreeWidgetItem(strings, type)
{
    init();
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(QTreeWidget *parent, int type) : QTreeWidgetItem(parent, type)
{
    init();
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(QTreeWidget *parent, const QStringList &strings, int type) : QTreeWidgetItem(parent, strings, type)
{
    init();
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(QTreeWidget *parent, PropertyTreeWidgetItem *preceding, int type) : QTreeWidgetItem(parent, preceding, type)
{
    init();
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(PropertyTreeWidgetItem *parent, int type) : QTreeWidgetItem(parent, type)
{
    init();
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(PropertyTreeWidgetItem *parent, const QStringList &strings, int type) : QTreeWidgetItem(parent, strings, type)
{
    init();
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(PropertyTreeWidgetItem *parent, PropertyTreeWidgetItem *preceding, int type) : QTreeWidgetItem(parent, preceding, type)
{
    init();
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(const PropertyTreeWidgetItem &other) : QTreeWidgetItem(other)
{
    init();
}

PropertyTreeWidgetItem::~PropertyTreeWidgetItem()
{
    delete mItemConnector;

    if (mMetaEnum)
    {
        delete mMetaEnum;
    }
}

inline void PropertyTreeWidgetItem::init()
{
    mItemConnector=new ItemConnector(this);
    mProperty=0;
    mFirstValue=QVariant();
    mDelegate=0;
    mMetaEnum=0;
    mModified=false;
}

void PropertyTreeWidgetItem::update(const QObjectList &aObjects)
{
    if (mProperty)
    {
        mProperty->update(this, aObjects);
    }
}

Property* PropertyTreeWidgetItem::topProperty()
{
    PropertyTreeWidgetItem* aCurItem=this;

    do
    {
        if (aCurItem->property())
        {
            return aCurItem->property();
        }

        QTreeWidgetItem *aParent=aCurItem->parent();

        if (aParent==0)
        {
            break;
        }

        aCurItem=(PropertyTreeWidgetItem *)aParent;
    } while (true);

    return 0;
}

// -------------------------------------------------------------------------------------

ItemConnector* PropertyTreeWidgetItem::itemConnector()
{
    return mItemConnector;
}

Property* PropertyTreeWidgetItem::property()
{
    return mProperty;
}

void PropertyTreeWidgetItem::setProperty(Property* aProperty)
{
    if (mProperty)
    {
        QObject::disconnect(mItemConnector, SIGNAL(valueChanged(QVariant)), mProperty, SIGNAL(valueChanged(QVariant)));
    }

    mProperty=aProperty;

    if (mProperty)
    {
        QObject::connect(mItemConnector, SIGNAL(valueChanged(QVariant)), mProperty, SIGNAL(valueChanged(QVariant)));
    }
}

QVariant PropertyTreeWidgetItem::firstValue() const
{
    return mFirstValue;
}

void PropertyTreeWidgetItem::setFirstValue(const QVariant &aFirstValue)
{
    mFirstValue=aFirstValue;
}

CustomDelegate* PropertyTreeWidgetItem::delegate() const
{
    return mDelegate;
}

void PropertyTreeWidgetItem::setDelegate(CustomDelegate *aDelegate)
{
    mDelegate=aDelegate;
}

QMetaEnum* PropertyTreeWidgetItem::metaEnum() const
{
    return mMetaEnum;
}

void PropertyTreeWidgetItem::setMetaEnum(const QMetaEnum &aMetaEnum)
{
    if (!mMetaEnum)
    {
        mMetaEnum=new QMetaEnum();
    }

    *mMetaEnum=aMetaEnum;
}

bool PropertyTreeWidgetItem::isModified() const
{
    return mModified;
}

void PropertyTreeWidgetItem::setModified(const bool &aModified)
{
    mModified=aModified;
}

