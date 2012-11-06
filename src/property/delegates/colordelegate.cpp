#include "colordelegate.h"

#include <QColor>

#include "../editors/coloreditor.h"
#include "../propertytreewidgetitem.h"

ColorDelegate::ColorDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* ColorDelegate::createEditor(QWidget *aParent) const
{
    return new ColorEditor(aParent);
}

void ColorDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    ColorEditor *aColorEditor=(ColorEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Color:
            aColorEditor->setValue(aItem->firstValue().value<QColor>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
