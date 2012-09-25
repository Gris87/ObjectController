#ifndef PROPERTYTREEWIDGETITEM_H
#define PROPERTYTREEWIDGETITEM_H

#include <QTreeWidgetItem>

#include "property.h"

class PropertyTreeWidgetItem : public QTreeWidgetItem
{
public:
    PropertyTreeWidgetItem(int type = Type);
    PropertyTreeWidgetItem(const QStringList &strings, int type = Type);
    PropertyTreeWidgetItem(QTreeWidget *parent, int type = Type);
    PropertyTreeWidgetItem(QTreeWidget *parent, const QStringList &strings, int type = Type);
    PropertyTreeWidgetItem(QTreeWidget *parent, PropertyTreeWidgetItem *preceding, int type = Type);
    PropertyTreeWidgetItem(PropertyTreeWidgetItem *parent, int type = Type);
    PropertyTreeWidgetItem(PropertyTreeWidgetItem *parent, const QStringList &strings, int type = Type);
    PropertyTreeWidgetItem(PropertyTreeWidgetItem *parent, PropertyTreeWidgetItem *preceding, int type = Type);
    PropertyTreeWidgetItem(const PropertyTreeWidgetItem &other);

    Property* property();
    void setProperty(Property* aProperty);

protected:
    Property* mProperty;
};

#endif // PROPERTYTREEWIDGETITEM_H
