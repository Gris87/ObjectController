#include "integerdelegate.h"

#include "../editors/integereditor.h"
#include "../propertytreewidgetitem.h"

IntegerDelegate::IntegerDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* IntegerDelegate::createEditor(QWidget *aParent) const
{
    return new IntegerEditor(aParent);
}

void IntegerDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    IntegerEditor *aIntegerEditor=(IntegerEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Int:
            aIntegerEditor->setValue(aItem->firstValue().toInt());
        break;
        case QVariant::UInt:
            aIntegerEditor->setValue(aItem->firstValue().toUInt());
        break;
        case QVariant::LongLong:
            aIntegerEditor->setValue(aItem->firstValue().toLongLong());
        break;
        case QVariant::ULongLong:
            aIntegerEditor->setValue(aItem->firstValue().toULongLong());
        break;
        case QMetaType::Char:
            aIntegerEditor->setValue((qint8)aItem->firstValue().toInt());
        break;
        case QMetaType::UChar:
            aIntegerEditor->setValue((quint8)aItem->firstValue().toUInt());
        break;
        case QMetaType::Short:
            aIntegerEditor->setValue((qint16)aItem->firstValue().toInt());
        break;
        case QMetaType::UShort:
            aIntegerEditor->setValue((quint16)aItem->firstValue().toUInt());
        break;
        case QMetaType::Long:
            aIntegerEditor->setValue((qint32)aItem->firstValue().toInt());
        break;
        case QMetaType::ULong:
            aIntegerEditor->setValue((quint32)aItem->firstValue().toUInt());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
