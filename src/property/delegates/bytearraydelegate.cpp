#include "bytearraydelegate.h"

#include "../editors/bytearrayeditor.h"
#include "../propertytreewidgetitem.h"

ByteArrayDelegate::ByteArrayDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* ByteArrayDelegate::createEditor(QWidget *aParent) const
{
    return new ByteArrayEditor(aParent);
}

void ByteArrayDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    ByteArrayEditor *aByteArrayEditor=(ByteArrayEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::ByteArray:
            aByteArrayEditor->setValue(aItem->firstValue().value<QByteArray>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
