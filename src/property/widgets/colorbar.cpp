#include "colorbar.h"

#include <QMouseEvent>
#include <QStyleOptionFrameV3>

ColorBar::ColorBar(QWidget *parent) :
    QWidget(parent)
{
    mLeftPressed=false;
    mColor.setRgb(255, 255, 255);
    mValue=255;
}

QColor ColorBar::color() const
{
    return mColor;
}

void ColorBar::setColor(const QColor &aColor)
{
    if (mColor!=aColor)
    {
        mColor=aColor;
        update();
    }
}

int ColorBar::value() const
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
    double aValue=(y-4)/((double)height()-8);

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

    QRect aBarRect(0, 3, width()-6, height()-7);
    paint.drawRect(aBarRect);
    drawFrame(&paint, aBarRect);



    int cursorY=4+((255-mValue)/255.0f)*(height()-9);

    QPolygon aPolygon;
    aPolygon.append(QPoint(width()-5, cursorY));
    aPolygon.append(QPoint(width(),   cursorY-5));
    aPolygon.append(QPoint(width(),   cursorY+5));

    paint.setBrush(QBrush(QColor(0, 0, 0)));
    paint.drawPolygon(aPolygon);
}

void ColorBar::drawFrame(QPainter *p, QRect aRect)
{
    QStyleOptionFrameV3 opt;

    aRect.setRight(aRect.right()+1);
    aRect.setBottom(aRect.bottom()+1);

    opt.init(this);

    opt.rect          = aRect;
    opt.lineWidth     = 1;
    opt.midLineWidth  = 0;
    opt.state        |= QStyle::State_Sunken;
    opt.frameShape    = QFrame::Panel;

    style()->drawControl(QStyle::CE_ShapedFrame, &opt, p, this);
}
