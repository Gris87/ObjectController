#include "itemconnector.h"

#include "propertytreewidgetitem.h"

ItemConnector::ItemConnector(PropertyTreeWidgetItem *aItem, QObject *parent) :
    QObject(parent)
{
    mItem=aItem;
}

PropertyTreeWidgetItem* ItemConnector::item()
{
    return mItem;
}
