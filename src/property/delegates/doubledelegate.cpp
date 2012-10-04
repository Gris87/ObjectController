#include "doubledelegate.h"

#include "../editors/doubleeditor.h"
#include "../propertytreewidgetitem.h"

DoubleDelegate::DoubleDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* DoubleDelegate::createEditor(QWidget *aParent) const
{
    return new DoubleEditor(aParent);
}

void DoubleDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    DoubleEditor *aDoubleEditor=(DoubleEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Double:
            aDoubleEditor->setValue(aItem->firstValue().toDouble());
        break;
        case QMetaType::Float:
            aDoubleEditor->setValue((float)aItem->firstValue().toDouble());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
