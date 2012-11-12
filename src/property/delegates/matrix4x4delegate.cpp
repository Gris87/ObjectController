#include "matrix4x4delegate.h"

#include "../editors/matrix4x4editor.h"
#include "../propertytreewidgetitem.h"

Matrix4x4Delegate::Matrix4x4Delegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* Matrix4x4Delegate::createEditor(QWidget *aParent) const
{
    return new Matrix4x4Editor(aParent);
}

void Matrix4x4Delegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    Matrix4x4Editor *aMatrix4x4Editor=(Matrix4x4Editor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Matrix4x4:
            aMatrix4x4Editor->setValue(aItem->firstValue().value<QMatrix4x4>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
