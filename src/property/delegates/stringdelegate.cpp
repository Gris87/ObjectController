#include "stringdelegate.h"

#include "../editors/stringeditor.h"
#include "../propertytreewidgetitem.h"

StringDelegate::StringDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* StringDelegate::createEditor(QWidget *aParent) const
{
    return new StringEditor(aParent);
}

void StringDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    StringEditor *aStringEditor=(StringEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::String:
            aStringEditor->setValue(aItem->firstValue().toString());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
