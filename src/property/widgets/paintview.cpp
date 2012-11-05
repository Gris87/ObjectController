#include "paintview.h"

#include <QMouseEvent>

PaintView::PaintView(QPixmap aPixmap, QWidget *parent) :
    QGraphicsView(parent)
{
    QGraphicsScene *aScene=new QGraphicsScene(0, 0, aPixmap.width(), aPixmap.height());
    mPixmapItem=aScene->addPixmap(aPixmap);
    setScene(aScene);
}

QPixmap PaintView::image() const
{
    return mPixmapItem->pixmap();
}

void PaintView::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {

    }
    else
    if (event->button()==Qt::RightButton)
    {

    }
}

void PaintView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {

    }
    else
    if (event->button()==Qt::RightButton)
    {

    }
}

QColor PaintView::firstColor() const
{
    return mFirstColor;
}

void PaintView::setFirstColor(const QColor &aColor)
{
    mFirstColor=aColor;
}

QColor PaintView::secondColor() const
{
    return mSecondColor;
}

void PaintView::setSecondColor(const QColor &aColor)
{
    mSecondColor=aColor;
}
