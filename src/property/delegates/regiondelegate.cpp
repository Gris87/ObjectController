#include "regiondelegate.h"

#include "../editors/regioneditor.h"
#include "../propertytreewidgetitem.h"

RegionDelegate::RegionDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* RegionDelegate::createEditor(QWidget *aParent) const
{
    return new RegionEditor(aParent);
}

void RegionDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    RegionEditor *aRegionEditor=(RegionEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Region:
            aRegionEditor->setValue(aItem->firstValue().value<QRegion>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
