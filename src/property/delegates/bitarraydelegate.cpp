#include "bitarraydelegate.h"

#include "../editors/bitarrayeditor.h"
#include "../propertytreewidgetitem.h"

BitArrayDelegate::BitArrayDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* BitArrayDelegate::createEditor(QWidget *aParent) const
{
    return new BitArrayEditor(aParent);
}

void BitArrayDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    BitArrayEditor *aBitArrayEditor=(BitArrayEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::BitArray:
            aBitArrayEditor->setValue(aItem->firstValue().value<QBitArray>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
