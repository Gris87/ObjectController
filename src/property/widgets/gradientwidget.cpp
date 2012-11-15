#include "gradientwidget.h"

#include <QMouseEvent>
#include <QStyleOptionFrameV3>

GradientWidget::GradientWidget(QWidget *parent) :
    QWidget(parent)
{
    mLeftPressed=false;
    mGradientStops.append(QGradientStop(0, QColor(255, 255, 255)));
    mGradientStops.append(QGradientStop(1, QColor(0, 0, 0)));
}

QSize GradientWidget::minimumSizeHint() const
{
    return QSize(100, 20);
}

QSize GradientWidget::sizeHint() const
{
    return QSize(208, 20);
}

QGradientStops GradientWidget::gradientStops() const
{
    return mGradientStops;
}

void GradientWidget::setGradientStops(const QGradientStops &aGradientStops)
{
    if (mGradientStops!=aGradientStops)
    {
        mGradientStops=aGradientStops;
        update();

        emit gradientChanged(mGradientStops);
    }
}

void GradientWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        mLeftPressed=true;
    }
}

void GradientWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mLeftPressed)
    {
    }
}

void GradientWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (mLeftPressed)
    {
        mLeftPressed=false;
    }
}

void GradientWidget::paintEvent(QPaintEvent * /*event*/)
{
    QPainter paint(this);

    QLinearGradient aGradient(0, 0, width(), 0);
    aGradient.setStops(mGradientStops);

    paint.setBrush(QBrush(aGradient));

    QRect aBarRect(4, 13, width()-9, height()-14);
    paint.drawRect(aBarRect);
    drawFrame(&paint, aBarRect);

    for (int i=0; i<mGradientStops.count(); ++i)
    {
        int cursorX=4+mGradientStops.at(i).first*(width()-9);

        QPolygon aPolygon;
        aPolygon.append(QPoint(cursorX,   13));
        aPolygon.append(QPoint(cursorX-4, 9));
        aPolygon.append(QPoint(cursorX+4, 9));

        paint.setBrush(QBrush(QColor(0, 0, 0)));
        paint.drawPolygon(aPolygon);



        QColor aColor=mGradientStops.at(i).second;
        QRect aColorRect=QRect(cursorX-4, 0, 8, 8);

        if (aColor.alpha()<255)
        {
            QRect aTransparentRect(aColorRect.left()+2, aColorRect.top()+2, aColorRect.width()-4, aColorRect.height()-4);
            drawTransparentArea(&paint, aTransparentRect, 3);
        }

        paint.fillRect(aColorRect, QBrush(aColor));
        drawFrame(&paint, aColorRect);
    }
}

void GradientWidget::drawTransparentArea(QPainter *aPainter, QRect aRect, int aBoxSize)
{
    int aCurRow=0;

    while ((aCurRow*aBoxSize)<aRect.height())
    {
        int aCurCol=0;

        while ((aCurCol*aBoxSize)<aRect.width())
        {
            int aRectWidth=aRect.width()-(aCurCol*aBoxSize);
            int aRectHeight=aRect.height()-(aCurRow*aBoxSize);

            if (aRectWidth>aBoxSize)
            {
                aRectWidth=aBoxSize;
            }

            if (aRectHeight>aBoxSize)
            {
                aRectHeight=aBoxSize;
            }



            if ((aCurRow + aCurCol) & 1)
            {
                aPainter->fillRect(aRect.left()+(aCurCol*aBoxSize), aRect.top()+(aCurRow*aBoxSize), aRectWidth, aRectHeight, QBrush(QColor(255, 255, 255)));
            }
            else
            {
                aPainter->fillRect(aRect.left()+(aCurCol*aBoxSize), aRect.top()+(aCurRow*aBoxSize), aRectWidth, aRectHeight, QBrush(QColor(0, 0, 0)));
            }



            ++aCurCol;
        }

        ++aCurRow;
    }
}

void GradientWidget::drawFrame(QPainter *p, QRect aRect)
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
