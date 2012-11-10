#include "textlengthdelegate.h"

#include "../editors/textlengtheditor.h"
#include "../propertytreewidgetitem.h"

TextLengthDelegate::TextLengthDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* TextLengthDelegate::createEditor(QWidget *aParent) const
{
    return new TextLengthEditor(aParent);
}

void TextLengthDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    TextLengthEditor *aTextLengthEditor=(TextLengthEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::TextLength:
            aTextLengthEditor->setValue(aItem->firstValue().value<QTextLength>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
