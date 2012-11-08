#include "linedelegate.h"

#include "../editors/lineeditor.h"
#include "../propertytreewidgetitem.h"

LineDelegate::LineDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* LineDelegate::createEditor(QWidget *aParent) const
{
    return new LineEditor(aParent);
}

void LineDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    LineEditor *aLineEditor=(LineEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Line:
            aLineEditor->setValue(aItem->firstValue().value<QLine>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
