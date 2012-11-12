#include "vector3ddelegate.h"

#include "../editors/vector3deditor.h"
#include "../propertytreewidgetitem.h"

Vector3DDelegate::Vector3DDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* Vector3DDelegate::createEditor(QWidget *aParent) const
{
    return new Vector3DEditor(aParent);
}

void Vector3DDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    Vector3DEditor *aVector3DEditor=(Vector3DEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Vector3D:
            aVector3DEditor->setValue(aItem->firstValue().value<QVector3D>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
