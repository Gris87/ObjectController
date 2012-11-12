#include "textformatdelegate.h"

#include "../editors/textformateditor.h"
#include "../propertytreewidgetitem.h"

TextFormatDelegate::TextFormatDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* TextFormatDelegate::createEditor(QWidget *aParent) const
{
    return new TextFormatEditor(aParent);
}

void TextFormatDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    TextFormatEditor *aTextFormatEditor=(TextFormatEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::TextFormat:
            aTextFormatEditor->setValue(aItem->firstValue().value<QTextFormat>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
