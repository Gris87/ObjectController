#include "customdelegate.h"

CustomDelegate::CustomDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

CustomEditor* CustomDelegate::createEditor(QWidget * /*aParent*/, PropertyTreeWidgetItem * /*aItem*/) const
{
    return 0;
}
