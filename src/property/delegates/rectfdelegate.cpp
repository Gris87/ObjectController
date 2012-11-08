#include "rectfdelegate.h"

#include "../editors/rectfeditor.h"
#include "../propertytreewidgetitem.h"

RectFDelegate::RectFDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* RectFDelegate::createEditor(QWidget *aParent) const
{
    return new RectFEditor(aParent);
}

void RectFDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    RectFEditor *aRectFEditor=(RectFEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::RectF:
            aRectFEditor->setValue(aItem->firstValue().value<QRectF>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
