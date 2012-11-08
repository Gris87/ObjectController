#include "pointfdelegate.h"

#include "../editors/pointfeditor.h"
#include "../propertytreewidgetitem.h"

PointFDelegate::PointFDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* PointFDelegate::createEditor(QWidget *aParent) const
{
    return new PointFEditor(aParent);
}

void PointFDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    PointFEditor *aPointFEditor=(PointFEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::PointF:
            aPointFEditor->setValue(aItem->firstValue().value<QPointF>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
