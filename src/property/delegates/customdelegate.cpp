#include "customdelegate.h"

#include "../propertytreewidgetitem.h"

CustomDelegate::CustomDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

CustomEditor* CustomDelegate::createEditor(QWidget * /*aParent*/) const
{
    return 0;
}

void CustomDelegate::setEditorData(QWidget * /*aEditor*/, PropertyTreeWidgetItem * /*aItem*/) const
{
    // Nothing
}
