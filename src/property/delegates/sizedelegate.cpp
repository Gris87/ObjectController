#include "sizedelegate.h"

#include "../editors/sizeeditor.h"
#include "../propertytreewidgetitem.h"

SizeDelegate::SizeDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* SizeDelegate::createEditor(QWidget *aParent) const
{
    return new SizeEditor(aParent);
}

void SizeDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    SizeEditor *aSizeEditor=(SizeEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Size:
            aSizeEditor->setValue(aItem->firstValue().value<QSize>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
