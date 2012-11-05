#include "fontdelegate.h"

#include "../editors/fonteditor.h"
#include "../propertytreewidgetitem.h"

FontDelegate::FontDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* FontDelegate::createEditor(QWidget *aParent) const
{
    return new FontEditor(aParent);
}

void FontDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    FontEditor *aFontEditor=(FontEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Font:
            aFontEditor->setValue(aItem->firstValue().value<QFont>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
