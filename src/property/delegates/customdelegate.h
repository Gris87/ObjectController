#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QItemDelegate>

class CustomDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit CustomDelegate(QObject *parent = 0);
};

#endif // CUSTOMDELEGATE_H
