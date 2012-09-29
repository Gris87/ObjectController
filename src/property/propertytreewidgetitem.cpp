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

inline void PropertyTreeWidgetItem::init()
{
    mProperty=0;
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

bool PropertyTreeWidgetItem::isModified() const
{
    return mModified;
}

void PropertyTreeWidgetItem::setModified(const bool aModified)
{
    mModified=aModified;
}

Property* PropertyTreeWidgetItem::property()
{
    return mProperty;
}

void PropertyTreeWidgetItem::setProperty(Property* aProperty)
{
    mProperty=aProperty;

    setText(0, mProperty->name());
}
