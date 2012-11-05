#include "paintview.h"

PaintView::PaintView(QPixmap aPixmap, QWidget *parent) :
    QGraphicsView(parent)
{
}

QPixmap PaintView::image() const
{
    return QPixmap();
}
