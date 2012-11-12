#include "transformdelegate.h"

#include "../editors/transformeditor.h"
#include "../propertytreewidgetitem.h"

TransformDelegate::TransformDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* TransformDelegate::createEditor(QWidget *aParent) const
{
    return new TransformEditor(aParent);
}

void TransformDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    TransformEditor *aTransformEditor=(TransformEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Transform:
            aTransformEditor->setValue(aItem->firstValue().value<QTransform>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
