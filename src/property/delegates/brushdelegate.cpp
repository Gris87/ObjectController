#include "brushdelegate.h"

#include <QBrush>

#include "../editors/brusheditor.h"
#include "../propertytreewidgetitem.h"

BrushDelegate::BrushDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* BrushDelegate::createEditor(QWidget *aParent) const
{
    return new BrushEditor(aParent);
}

void BrushDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    BrushEditor *aBrushEditor=(BrushEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Brush:
            aBrushEditor->setValue(aItem->firstValue().value<QBrush>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
