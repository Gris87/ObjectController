#include "sizefdelegate.h"

#include "../editors/sizefeditor.h"
#include "../propertytreewidgetitem.h"

SizeFDelegate::SizeFDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* SizeFDelegate::createEditor(QWidget *aParent) const
{
    return new SizeFEditor(aParent);
}

void SizeFDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    SizeFEditor *aSizeFEditor=(SizeFEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::SizeF:
            aSizeFEditor->setValue(aItem->firstValue().value<QSizeF>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
