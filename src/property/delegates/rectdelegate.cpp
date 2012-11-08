#include "rectdelegate.h"

#include "../editors/recteditor.h"
#include "../propertytreewidgetitem.h"

RectDelegate::RectDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* RectDelegate::createEditor(QWidget *aParent) const
{
    return new RectEditor(aParent);
}

void RectDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    RectEditor *aRectEditor=(RectEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Rect:
            aRectEditor->setValue(aItem->firstValue().value<QRect>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
