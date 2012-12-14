#include "gradientwidget.h"

#include <QMouseEvent>
#include <QStyleOptionFrameV3>
#include <QVector4D>

#ifdef OBJECT_CONTROLLER
#include "../dialogs/coloreditdialog.h"
#else
#include "coloreditdialog.h"
#endif

GradientWidget::GradientWidget(const PropertyAttributes *aAttributes, QWidget *parent) :
    QWidget(parent)
{
    mLeftPressed=false;
    mStartX=0;
    mStartY=0;
    mSelectedIndex=-1;
    mDragging=false;

    mAttributes=aAttributes;

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
        mStartX=event->x();
        mStartY=event->y();
        mSelectedIndex=-1;

        for (int i=mGradientStops.count()-1; i>=0; --i)
        {
            int cursorX=4+qBound<qreal>(0, mGradientStops.at(i).first, 1)*(width()-9);

            if (mStartX>=cursorX-4 && mStartY>=0 && mStartX<=cursorX+4 && mStartY<=8)
            {
                mSelectedIndex=i;
                break;
            }
        }
    }
}

void GradientWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mLeftPressed)
    {
        mDragging=mDragging || qAbs(mStartX-event->x())>4 || qAbs(mStartY-event->y())>4;

        if (mSelectedIndex>=0 && mDragging)
        {
            mGradientStops[mSelectedIndex].first=qBound<qreal>(0, (event->x()-4)/((double)width()-8), 1);
            update();

            emit gradientChanged(mGradientStops);
        }
    }
}

void GradientWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (mLeftPressed)
    {
        if (mDragging)
        {
            if (
                mSelectedIndex>=0
                &&
                mGradientStops.count()>1
                &&
                (
                 event->x()<-50
                 ||
                 event->x()>width()+50
                 ||
                 event->y()<-50
                 ||
                 event->y()>height()+50
                )
               )
            {
                mGradientStops.remove(mSelectedIndex);
                update();

                emit gradientChanged(mGradientStops);
            }
        }
        else
        {
            if (mSelectedIndex>=0)
            {
                ColorEditDialog dialog(mGradientStops.at(mSelectedIndex).second, mAttributes, this);

                if (dialog.exec())
                {
                    mGradientStops[mSelectedIndex].second=dialog.selectedColor();
                    update();

                    emit gradientChanged(mGradientStops);
                }
            }
            else
            {
                QGradientStop aNewStop;

                aNewStop.first=qBound<qreal>(0, (event->x()-4)/((double)width()-8), 1);

                int aLeftStop=-1;
                int aRightStop=-1;
                qreal aMinDistance;

                aMinDistance=INT_MAX;

                for (int i=0; i<mGradientStops.count(); ++i)
                {
                    if (mGradientStops.at(i).first<=aNewStop.first)
                    {
                        if (aLeftStop<0 || aNewStop.first-mGradientStops.at(i).first<=aMinDistance)
                        {
                            aMinDistance=aNewStop.first-mGradientStops.at(i).first;
                            aLeftStop=i;
                        }
                    }
                }

                aMinDistance=INT_MAX;

                for (int i=0; i<mGradientStops.count(); ++i)
                {
                    if (mGradientStops.at(i).first>=aNewStop.first)
                    {
                        if (aRightStop<0 || mGradientStops.at(i).first-aNewStop.first<=aMinDistance)
                        {
                            aMinDistance=mGradientStops.at(i).first-aNewStop.first;
                            aRightStop=i;
                        }
                    }
                }



                if (aLeftStop<0 && aRightStop>=0)
                {
                    aNewStop.second=mGradientStops.at(aRightStop).second;
                }
                else
                if (aLeftStop>=0 && aRightStop<0)
                {
                    aNewStop.second=mGradientStops.at(aLeftStop).second;
                }
                else
                {
                    QVector4D aStartColor=QVector4D(
                                                    mGradientStops.at(aLeftStop).second.red()/255.0f,
                                                    mGradientStops.at(aLeftStop).second.green()/255.0f,
                                                    mGradientStops.at(aLeftStop).second.blue()/255.0f,
                                                    mGradientStops.at(aLeftStop).second.alpha()/255.0f
                                                   );

                    QVector4D aEndColor=QVector4D(
                                                  mGradientStops.at(aRightStop).second.red()/255.0f,
                                                  mGradientStops.at(aRightStop).second.green()/255.0f,
                                                  mGradientStops.at(aRightStop).second.blue()/255.0f,
                                                  mGradientStops.at(aRightStop).second.alpha()/255.0f
                                                 );

                    QVector4D aDeltaColor=aEndColor-aStartColor;

                    qreal aPos=aNewStop.first-mGradientStops.at(aLeftStop).first;
                    qreal aTotal=mGradientStops.at(aRightStop).first-mGradientStops.at(aLeftStop).first;

                    QVector4D aNewColor=aStartColor+aDeltaColor*(aPos/aTotal);

                    aNewStop.second.setRgb(
                                           qBound<int>(0, aNewColor.x()*255, 255),
                                           qBound<int>(0, aNewColor.y()*255, 255),
                                           qBound<int>(0, aNewColor.z()*255, 255),
                                           qBound<int>(0, aNewColor.w()*255, 255)
                                          );
                }



                mGradientStops.append(aNewStop);
                update();

                emit gradientChanged(mGradientStops);
            }
        }

        mLeftPressed=false;
        mDragging=false;
    }
}

void GradientWidget::paintEvent(QPaintEvent * /*event*/)
{
    QPainter paint(this);

    QLinearGradient aGradient(0, 0, width(), 0);
    aGradient.setStops(mGradientStops);

    paint.setBrush(QBrush(aGradient));

    QRect aBarRect(3, 14, width()-7, height()-15);
    paint.drawRect(aBarRect);
    drawFrame(&paint, aBarRect);

    for (int i=0; i<mGradientStops.count(); ++i)
    {
        int cursorX=4+qBound<qreal>(0, mGradientStops.at(i).first, 1)*(width()-9);

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
            QRect aTransparentRect(aColorRect.left()+1, aColorRect.top()+1, aColorRect.width()-2, aColorRect.height()-2);
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
