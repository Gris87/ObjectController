#ifndef PROPERTYITEMDELEGATE_H
#define PROPERTYITEMDELEGATE_H

#include <QItemDelegate>

class PropertyItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit PropertyItemDelegate(QObject *parent = 0);

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // PROPERTYITEMDELEGATE_H
