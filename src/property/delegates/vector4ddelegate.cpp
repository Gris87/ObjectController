#include "vector4ddelegate.h"

#include "../editors/vector4deditor.h"
#include "../propertytreewidgetitem.h"

Vector4DDelegate::Vector4DDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* Vector4DDelegate::createEditor(QWidget *aParent) const
{
    return new Vector4DEditor(aParent);
}

void Vector4DDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    Vector4DEditor *aVector4DEditor=(Vector4DEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Vector4D:
            aVector4DEditor->setValue(aItem->firstValue().value<QVector4D>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
