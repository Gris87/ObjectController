#ifndef PROPERTYTREEWIDGETITEM_H
#define PROPERTYTREEWIDGETITEM_H

#include <QTreeWidgetItem>

#include "property.h"

#include "delegates/customdelegate.h"

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

    void update(const QObjectList &aObjects);

    // -------------------------------------------------------------------------------------

    Property*       property();
    void            setProperty(Property* aProperty);

    QVariant        firstValue() const;
    void            setFirstValue(const QVariant &aFirstValue);

    CustomDelegate* delegate() const;
    void            setDelegate(CustomDelegate *aDelegate);

    bool            isModified() const;
    void            setModified(const bool &aModified);

protected:
    Property*       mProperty;
    QVariant        mFirstValue;
    CustomDelegate* mDelegate;
    bool            mModified;

    void init();
};

#endif // PROPERTYTREEWIDGETITEM_H
