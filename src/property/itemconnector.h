#ifndef ITEMCONNECTOR_H
#define ITEMCONNECTOR_H

#include <QObject>

class PropertyTreeWidgetItem;

class ItemConnector : public QObject
{
    Q_OBJECT
public:
    explicit ItemConnector(PropertyTreeWidgetItem *aItem, QObject *parent=0);

    void sendSignal();

    PropertyTreeWidgetItem *item();

protected:
    PropertyTreeWidgetItem *mItem;

signals:
    void valueChanged(const QVariant &aNewValue);
};

#endif // ITEMCONNECTOR_H
