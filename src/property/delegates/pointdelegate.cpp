#include "pointdelegate.h"

#include "../editors/pointeditor.h"
#include "../propertytreewidgetitem.h"

PointDelegate::PointDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* PointDelegate::createEditor(QWidget *aParent) const
{
    return new PointEditor(aParent);
}

void PointDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    PointEditor *aPointEditor=(PointEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Point:
            aPointEditor->setValue(aItem->firstValue().value<QPoint>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
