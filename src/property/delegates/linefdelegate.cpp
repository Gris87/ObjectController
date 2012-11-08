#include "linefdelegate.h"

#include "../editors/linefeditor.h"
#include "../propertytreewidgetitem.h"

LineFDelegate::LineFDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* LineFDelegate::createEditor(QWidget *aParent) const
{
    return new LineFEditor(aParent);
}

void LineFDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    LineFEditor *aLineFEditor=(LineFEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::LineF:
            aLineFEditor->setValue(aItem->firstValue().value<QLineF>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
