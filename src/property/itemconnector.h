#ifndef ITEMCONNECTOR_H
#define ITEMCONNECTOR_H

#include <QObject>

class ItemConnector : public QObject
{
    Q_OBJECT
public:
    explicit ItemConnector(QObject *parent=0);

signals:
    void valueChanged(const QVariant &aNewValue);
};

#endif // ITEMCONNECTOR_H
