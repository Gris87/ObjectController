#include "vector2ddelegate.h"

#include "../editors/vector2deditor.h"
#include "../propertytreewidgetitem.h"

Vector2DDelegate::Vector2DDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* Vector2DDelegate::createEditor(QWidget *aParent) const
{
    return new Vector2DEditor(aParent);
}

void Vector2DDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    Vector2DEditor *aVector2DEditor=(Vector2DEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Vector2D:
            aVector2DEditor->setValue(aItem->firstValue().value<QVector2D>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
