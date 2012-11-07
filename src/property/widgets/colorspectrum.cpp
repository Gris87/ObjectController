#include "colorspectrum.h"

#include <QPainter>
#include <QMouseEvent>

ColorSpectrum::ColorSpectrum(QWidget *parent) :
    QFrame(parent)
{
    mLeftPressed=false;

    setFrameShadow(QFrame::Sunken);
    setFrameShape(QFrame::Panel);

    updateSpectrum();
}

void ColorSpectrum::setColor(QColor aColor)
{
    if (mColor!=aColor)
    {
        mColor=aColor;
        update();

        emit colorChanged(mColor);
    }
}

QColor ColorSpectrum::color()
{
    return mColor;
}

void ColorSpectrum::setColorAt(int x, int y)
{
    double aHue=x/(double)width();
    double aSat=y/(double)height();

    setColor(QColor::fromHsv(
                             qBound<int>(0, aHue*359, 359),
                             255-qBound<int>(0, aSat*255, 255),
                             255
                            ));
}

void ColorSpectrum::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);
    updateSpectrum();
}

void ColorSpectrum::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        mLeftPressed=true;
        setColorAt(event->x(), event->y());
    }
}

void ColorSpectrum::mouseMoveEvent(QMouseEvent *event)
{
    if (mLeftPressed)
    {
        setColorAt(event->x(), event->y());
    }
}

void ColorSpectrum::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    mLeftPressed=false;
}

void ColorSpectrum::paintEvent(QPaintEvent * /*event*/)
{
    QPainter paint(this);

    paint.drawPixmap(0, 0, mSpectrumPixmap);

    int cursorX=mColor.hueF()*width();
    int cursorY=(1-mColor.saturationF())*height();

    paint.setPen(QPen(QBrush(QColor(0, 0, 0)), 2));
    paint.drawLine(cursorX,    cursorY-10, cursorX,    cursorY+10);
    paint.drawLine(cursorX-10, cursorY,    cursorX+10, cursorY);

    drawFrame(&paint);
}

void ColorSpectrum::updateSpectrum()
{
    int aWidth=width();
    int aHeight=height();

    mSpectrumPixmap=QPixmap(aWidth, aHeight);

    QPainter paint(&mSpectrumPixmap);

    QPen aPen;

    for (int i=0; i<aHeight; ++i)
    {
        for (int j=0; j<aWidth; ++j)
        {
            aPen.setColor(QColor::fromHsvF(j/(double)aWidth, 1-i/(double)aHeight, 0.8));

            paint.setPen(aPen);
            paint.drawPoint(j, i);
        }
    }
}
