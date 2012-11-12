#include "quaterniondelegate.h"

#include "../editors/quaternioneditor.h"
#include "../propertytreewidgetitem.h"

QuaternionDelegate::QuaternionDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* QuaternionDelegate::createEditor(QWidget *aParent) const
{
    return new QuaternionEditor(aParent);
}

void QuaternionDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    QuaternionEditor *aQuaternionEditor=(QuaternionEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Quaternion:
            aQuaternionEditor->setValue(aItem->firstValue().value<QQuaternion>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
