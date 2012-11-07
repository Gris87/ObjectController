#include "colorbar.h"

#include <QPainter>
#include <QMouseEvent>

ColorBar::ColorBar(QWidget *parent) :
    QWidget(parent)
{
    mLeftPressed=false;
    mColor.setRgb(255, 255, 255);
    mValue=255;
}

QColor ColorBar::color()
{
    return mColor;
}

void ColorBar::setColor(QColor aColor)
{
    if (mColor!=aColor)
    {
        mColor=aColor;
        update();
    }
}

int ColorBar::value()
{
    return mValue;
}

void ColorBar::setValue(int aValue)
{
    aValue=qBound<int>(0, aValue, 255);

    if (mValue!=aValue)
    {
        mValue=aValue;
        update();

        emit valueChanged(mValue);
    }
}

void ColorBar::setValueAt(int y)
{
    double aValue=(y-4)/(double)height();

    setValue(255-aValue*255);
}

void ColorBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        mLeftPressed=true;
        setValueAt(event->y());
    }
}

void ColorBar::mouseMoveEvent(QMouseEvent *event)
{
    if (mLeftPressed)
    {
        setValueAt(event->y());
    }
}

void ColorBar::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    mLeftPressed=false;
}

void ColorBar::paintEvent(QPaintEvent * /*event*/)
{
    QPainter paint(this);

    QLinearGradient aGradient(0, 0, 0, height());
    aGradient.setColorAt(0, QColor::fromHsv(mColor.hue(), mColor.saturation(), 255));
    aGradient.setColorAt(1, QColor(0, 0, 0));

    paint.setBrush(QBrush(aGradient));
    paint.drawRect(0, 4, width()-5, height()-8);

    int cursorY=4+((255-mValue)/255.0f)*(height()-8);

    QPolygon aPolygon;
    aPolygon.append(QPoint(width()-4, cursorY));
    aPolygon.append(QPoint(width(), cursorY-4));
    aPolygon.append(QPoint(width(), cursorY+4));

    paint.setBrush(QBrush(QColor(0, 0, 0)));
    paint.drawPolygon(aPolygon);
}
