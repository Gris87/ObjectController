#include "enumdelegate.h"

#include "../editors/enumeditor.h"
#include "../propertytreewidgetitem.h"

EnumDelegate::EnumDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* EnumDelegate::createEditor(QWidget *aParent) const
{
    return new EnumEditor(aParent);
}

void EnumDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    EnumEditor *aEnumEditor=(EnumEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Int:
        case QVariant::UInt:
        case QVariant::LongLong:
        case QVariant::ULongLong:
        case QMetaType::Char:
        case QMetaType::UChar:
        case QMetaType::Short:
        case QMetaType::UShort:
        case QMetaType::Long:
        case QMetaType::ULong:
            aEnumEditor->setValue(aItem->metaEnum(), aItem->firstValue().value<int>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
