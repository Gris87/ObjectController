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
    if (mMetaEnum)
    {
        delete mMetaEnum;
    }
}

inline void PropertyTreeWidgetItem::init()
{
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

// -------------------------------------------------------------------------------------

Property* PropertyTreeWidgetItem::property()
{
    return mProperty;
}

void PropertyTreeWidgetItem::setProperty(Property* aProperty)
{
    mProperty=aProperty;
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

void PropertyTreeWidgetItem::setMetaEnum(QMetaEnum *aMetaEnum)
{
    if (aMetaEnum)
    {
        if (!mMetaEnum)
        {
            mMetaEnum=new QMetaEnum();
        }

        *mMetaEnum=*aMetaEnum;
    }
    else
    {
        if (mMetaEnum)
        {
            delete mMetaEnum;
            mMetaEnum=0;
        }
    }
}

bool PropertyTreeWidgetItem::isModified() const
{
    return mModified;
}

void PropertyTreeWidgetItem::setModified(const bool &aModified)
{
    mModified=aModified;
}

