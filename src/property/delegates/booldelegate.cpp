#include "booldelegate.h"

#include "../editors/booleditor.h"
#include "../propertytreewidgetitem.h"

BoolDelegate::BoolDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* BoolDelegate::createEditor(QWidget *aParent) const
{
    return new BoolEditor(aParent);
}

void BoolDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    BoolEditor *aBoolEditor=(BoolEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Bool:
            aBoolEditor->setValue(aItem->firstValue().value<bool>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
