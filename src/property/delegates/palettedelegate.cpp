#include "palettedelegate.h"

#include <QPalette>

#include "../editors/paletteeditor.h"
#include "../propertytreewidgetitem.h"

PaletteDelegate::PaletteDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* PaletteDelegate::createEditor(QWidget *aParent) const
{
    return new PaletteEditor(aParent);
}

void PaletteDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    PaletteEditor *aPaletteEditor=(PaletteEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Palette:
            aPaletteEditor->setValue(aItem->firstValue().value<QPalette>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
