#include "stringlistdelegate.h"

#include "../editors/stringlisteditor.h"
#include "../propertytreewidgetitem.h"

StringListDelegate::StringListDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* StringListDelegate::createEditor(QWidget *aParent) const
{
    return new StringListEditor(aParent);
}

void StringListDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    StringListEditor *aStringListEditor=(StringListEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::StringList:
            aStringListEditor->setValue(aItem->firstValue().value<QStringList>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
