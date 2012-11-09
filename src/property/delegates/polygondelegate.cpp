#include "polygondelegate.h"

#include "../editors/polygoneditor.h"
#include "../propertytreewidgetitem.h"

PolygonDelegate::PolygonDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* PolygonDelegate::createEditor(QWidget *aParent) const
{
    return new PolygonEditor(aParent);
}

void PolygonDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    PolygonEditor *aPolygonEditor=(PolygonEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Polygon:
            aPolygonEditor->setValue(aItem->firstValue().value<QPolygon>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
