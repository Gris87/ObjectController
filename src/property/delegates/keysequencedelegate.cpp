#include "keysequencedelegate.h"

#include "../editors/keysequenceeditor.h"
#include "../propertytreewidgetitem.h"

KeySequenceDelegate::KeySequenceDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* KeySequenceDelegate::createEditor(QWidget *aParent) const
{
    return new KeySequenceEditor(aParent);
}

void KeySequenceDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    KeySequenceEditor *aKeySequenceEditor=(KeySequenceEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::KeySequence:
            aKeySequenceEditor->setValue(aItem->firstValue().value<QKeySequence>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
