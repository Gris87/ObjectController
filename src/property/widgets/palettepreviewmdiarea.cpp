#include "palettepreviewmdiarea.h"

#include <QPainter>

#include "../widgets/palettedemowidget.h"

PalettePreviewMdiArea::PalettePreviewMdiArea(QWidget *parent) :
    QMdiArea(parent)
{
    mDemoWidget=addSubWindow(new PaletteDemoWidget(this), Qt::SubWindow | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    mDemoWidget->setWindowState(Qt::WindowMaximized);
}

void PalettePreviewMdiArea::paintEvent(QPaintEvent * /*event*/)
{
    QPainter p(viewport());
    p.fillRect(rect(), palette().color(backgroundRole()).dark());
    p.setPen(QPen(Qt::white));
    p.drawText(0, height() / 2,  width(), height(), Qt::AlignHCenter, "Sorry, but there is no easter egg");
}

void PalettePreviewMdiArea::setEnabledState()
{
    setActiveSubWindow(mDemoWidget);
    mDemoWidget->setEnabled(true);
}

void PalettePreviewMdiArea::setDisabledState()
{
    setActiveSubWindow(mDemoWidget);
    mDemoWidget->setEnabled(false);
}

void PalettePreviewMdiArea::setInactiveState()
{
    setActiveSubWindow(0);
    mDemoWidget->setEnabled(true);
}

void PalettePreviewMdiArea::setPreviewPalette(QPalette aPalette)
{
    mDemoWidget->setPalette(aPalette);
}
