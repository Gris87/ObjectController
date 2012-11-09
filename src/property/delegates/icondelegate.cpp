#include "icondelegate.h"

#include "../editors/iconeditor.h"
#include "../propertytreewidgetitem.h"

IconDelegate::IconDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* IconDelegate::createEditor(QWidget *aParent) const
{
    return new IconEditor(aParent);
}

void IconDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    IconEditor *aIconEditor=(IconEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Icon:
            aIconEditor->setValue(aItem->firstValue().value<QIcon>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
