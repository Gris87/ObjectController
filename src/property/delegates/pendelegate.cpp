#include "pendelegate.h"

#include "../editors/peneditor.h"
#include "../propertytreewidgetitem.h"

PenDelegate::PenDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* PenDelegate::createEditor(QWidget *aParent) const
{
    return new PenEditor(aParent);
}

void PenDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    PenEditor *aPenEditor=(PenEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Pen:
            aPenEditor->setValue(aItem->firstValue().value<QPen>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
