#include "sizepolicydelegate.h"

#include "../editors/sizepolicyeditor.h"
#include "../propertytreewidgetitem.h"

SizePolicyDelegate::SizePolicyDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* SizePolicyDelegate::createEditor(QWidget *aParent) const
{
    return new SizePolicyEditor(aParent);
}

void SizePolicyDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    SizePolicyEditor *aSizePolicyEditor=(SizePolicyEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::SizePolicy:
            aSizePolicyEditor->setValue(aItem->firstValue().value<QSizePolicy>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
