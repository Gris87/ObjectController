#include "palettepreviewmdiarea.h"

#include <QPainter>

PalettePreviewMdiArea::PalettePreviewMdiArea(QWidget *parent) :
    QMdiArea(parent)
{
}

void PalettePreviewMdiArea::paintEvent(QPaintEvent * /*event*/)
{
    QPainter p(viewport());
    p.fillRect(rect(), palette().color(backgroundRole()).dark());
    p.setPen(QPen(Qt::white));
    p.drawText(0, height() / 2,  width(), height(), Qt::AlignHCenter, "Sorry, but there is no easter egg");
}
