#include "itemconnector.h"

#include "propertytreewidgetitem.h"

ItemConnector::ItemConnector(PropertyTreeWidgetItem *aItem, QObject *parent) :
    QObject(parent)
{
    mItem=aItem;
}

QObject* ItemConnector::sender()
{
    return QObject::sender();
}

void ItemConnector::sendSignal()
{
    emit valueChanged(mItem->firstValue());
}

PropertyTreeWidgetItem* ItemConnector::item()
{
    return mItem;
}
