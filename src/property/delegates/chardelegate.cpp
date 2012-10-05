#include "chardelegate.h"

#include "../editors/chareditor.h"
#include "../propertytreewidgetitem.h"

CharDelegate::CharDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* CharDelegate::createEditor(QWidget *aParent) const
{
    return new CharEditor(aParent);
}

void CharDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    CharEditor *aCharEditor=(CharEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Char:
            aCharEditor->setValue(aItem->firstValue().toChar());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
