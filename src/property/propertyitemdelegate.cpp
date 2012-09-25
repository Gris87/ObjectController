#include "propertyitemdelegate.h"

PropertyItemDelegate::PropertyItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QSize PropertyItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index) + QSize(6, 6);
}
