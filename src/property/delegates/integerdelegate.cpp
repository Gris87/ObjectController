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
            aIntegerEditor->setValue(aItem->firstValue().value<qint32>());
        break;
        case QVariant::UInt:
            aIntegerEditor->setValue(aItem->firstValue().value<quint32>());
        break;
        case QVariant::LongLong:
            aIntegerEditor->setValue(aItem->firstValue().value<qint64>());
        break;
        case QVariant::ULongLong:
            aIntegerEditor->setValue(aItem->firstValue().value<quint64>());
        break;
        case QMetaType::Char:
            aIntegerEditor->setValue(aItem->firstValue().value<qint8>());
        break;
        case QMetaType::UChar:
            aIntegerEditor->setValue(aItem->firstValue().value<quint8>());
        break;
        case QMetaType::Short:
            aIntegerEditor->setValue(aItem->firstValue().value<qint16>());
        break;
        case QMetaType::UShort:
            aIntegerEditor->setValue(aItem->firstValue().value<quint16>());
        break;
        case QMetaType::Long:
            aIntegerEditor->setValue(aItem->firstValue().value<qint32>());
        break;
        case QMetaType::ULong:
            aIntegerEditor->setValue(aItem->firstValue().value<quint32>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
