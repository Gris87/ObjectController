#include "cursordelegate.h"

#include "../editors/cursoreditor.h"
#include "../propertytreewidgetitem.h"

CursorDelegate::CursorDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* CursorDelegate::createEditor(QWidget *aParent) const
{
    return new CursorEditor(aParent);
}

void CursorDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    CursorEditor *aCursorEditor=(CursorEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Cursor:
            aCursorEditor->setValue(aItem->firstValue().value<QCursor>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
