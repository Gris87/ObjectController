#include "propertytreewidgetitem.h"

PropertyTreeWidgetItem::PropertyTreeWidgetItem(int type) : QTreeWidgetItem(type)
{
    mProperty=0;
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(const QStringList &strings, int type) : QTreeWidgetItem(strings, type)
{
    mProperty=0;
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(QTreeWidget *parent, int type) : QTreeWidgetItem(parent, type)
{
    mProperty=0;
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(QTreeWidget *parent, const QStringList &strings, int type) : QTreeWidgetItem(parent, strings, type)
{
    mProperty=0;
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(QTreeWidget *parent, PropertyTreeWidgetItem *preceding, int type) : QTreeWidgetItem(parent, preceding, type)
{
    mProperty=0;
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(PropertyTreeWidgetItem *parent, int type) : QTreeWidgetItem(parent, type)
{
    mProperty=0;
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(PropertyTreeWidgetItem *parent, const QStringList &strings, int type) : QTreeWidgetItem(parent, strings, type)
{
    mProperty=0;
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(PropertyTreeWidgetItem *parent, PropertyTreeWidgetItem *preceding, int type) : QTreeWidgetItem(parent, preceding, type)
{
    mProperty=0;
}

PropertyTreeWidgetItem::PropertyTreeWidgetItem(const PropertyTreeWidgetItem &other) : QTreeWidgetItem(other)
{
    mProperty=0;
}

void PropertyTreeWidgetItem::update(const QObjectList &aObjects)
{
    if (mProperty==0)
    {
        return;
    }

    setText(1, mProperty->read(aObjects).toString());
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
