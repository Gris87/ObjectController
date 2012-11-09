#include "pixmapdelegate.h"

#include <QPixmap>
#include <QImage>
#include <QBitmap>

#include "../editors/pixmapeditor.h"
#include "../propertytreewidgetitem.h"

PixmapDelegate::PixmapDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* PixmapDelegate::createEditor(QWidget *aParent) const
{
    return new PixmapEditor(aParent);
}

void PixmapDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    PixmapEditor *aPixmapEditor=(PixmapEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Pixmap:
            aPixmapEditor->setValue(aItem->firstValue().value<QPixmap>());
        break;
        case QVariant::Image:
            aPixmapEditor->setValue(aItem->firstValue().value<QImage>());
        break;
        case QVariant::Bitmap:
            aPixmapEditor->setValue(aItem->firstValue().value<QBitmap>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
