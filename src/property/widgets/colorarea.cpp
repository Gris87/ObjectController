#include "colorarea.h"

#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QGridLayout>
#include <QPainter>

#ifdef OBJECT_CONTROLLER
#include "../dialogs/coloreditdialog.h"
#else
#include "coloreditdialog.h"
#endif

ColorArea::ColorArea(QWidget *parent) :
    QFrame(parent)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    setFrameShadow(QFrame::Sunken);
    setFrameShape(QFrame::StyledPanel);

    mColor.setRgb(0, 0, 0);

    mTransparentBlockSize=8;

    mNeedDrawFrame=true;
    mSelected=false;
    mSelectAllowed=true;
    mPopupAllowed=true;

    mPopupCount=9;
    mPopupCellSize=9;
}

void ColorArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        if (mSelectAllowed)
        {
            ColorEditDialog dialog(color(), this);

            if (dialog.exec())
            {
                setColor(dialog.selectedColor());
            }
        }
        else
        {
            emit clicked();
        }
    }
    else
    if (event->button()==Qt::RightButton)
    {
        if (mPopupAllowed)
        {
            mPopupWidget=new QWidget(this, Qt::Popup);

            int aWidthSize=mPopupCellSize*mPopupCount*mPopupCount+4;
            int aHeightSize=mPopupCellSize*mPopupCount+4;

            int aX=cursor().pos().x();
            int aY=cursor().pos().y();

            QDesktopWidget *desktop = QApplication::desktop();
            QRect aScreenRect=desktop->screenGeometry();
            int aWidth = aScreenRect.right();
            int aHeight = aScreenRect.bottom();

            if (aX+aWidthSize>aWidth)
            {
                aX=aWidth-aWidthSize;
            }

            if (aY+aHeightSize>aHeight)
            {
                aY=aHeight-aHeightSize;
            }

            mPopupWidget->setGeometry(aX, aY, aWidthSize, aHeightSize);

            QGridLayout *aLayout=new QGridLayout(mPopupWidget);
            aLayout->setHorizontalSpacing(0);
            aLayout->setVerticalSpacing(0);
            aLayout->setContentsMargins(2, 2, 2, 2);

            quint16 aDiffY=255/(mPopupCount-1);
            quint32 aDiffX=65535/(mPopupCount*mPopupCount-1);

            for (int i=0; i<mPopupCount; i++)
            {
                for (int j=0; j<mPopupCount*mPopupCount; j++)
                {
                    ColorArea *aArea=new ColorArea(this);

                    aArea->mPopupAllowed=false;
                    aArea->mSelectAllowed=false;
                    aArea->mNeedDrawFrame=false;

                    aArea->setColor(QColor(aDiffY*i, aDiffX*j>>8, aDiffX*j & 0xFF));

                    connect(aArea, SIGNAL(clicked()), this, SLOT(cellClicked()));

                    aLayout->addWidget(aArea, i, j);
                }
            }

            mPopupWidget->show();
        }
        else
        {
            emit rightClicked();
        }
    }
}

void ColorArea::paintEvent(QPaintEvent * /*event*/)
{
    QRect aFrameRect=frameRect();

    QPainter paint(this);

    if (mColor.alpha()<255)
    {
        QRect aTransparentRect(aFrameRect.left()+1, aFrameRect.top()+1, aFrameRect.width()-2, aFrameRect.height()-2);
        drawTransparentArea(&paint, aTransparentRect, mTransparentBlockSize);
    }

    paint.fillRect(aFrameRect, QBrush(mColor));

    if (mNeedDrawFrame)
    {
        drawFrame(&paint);
    }

    if (mSelected)
    {
        paint.setPen(QPen(QBrush(QColor(0, 0, 0)), 1, Qt::DotLine));
        paint.drawRect(0, 0, width()-1, height()-1);
    }
}

void ColorArea::drawTransparentArea(QPainter *aPainter, QRect aRect, int aBoxSize)
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

void ColorArea::cellClicked()
{
    ColorArea *aArea=(ColorArea *)sender();

    setColor(aArea->color());

    delete mPopupWidget;
    mPopupWidget=0;
}

QSize ColorArea::minimumSizeHint() const
{
    return QSize(8, 8);
}

QSize ColorArea::sizeHint() const
{
    return QSize(20, 20);
}

// ********************************************************************************************

QColor ColorArea::color() const
{
    return mColor;
}

void ColorArea::setColor(const QColor &aColor)
{
    if (mColor!=aColor)
    {
        mColor=aColor;
        update();

        emit colorChanged(aColor);
    }
}

int ColorArea::transparentBlockSize() const
{
    return mTransparentBlockSize;
}

void ColorArea::setTransparentBlockSize(const int &aTransparentBlockSize)
{
    if (mTransparentBlockSize!=aTransparentBlockSize)
    {
        mTransparentBlockSize=aTransparentBlockSize;
        update();
    }
}

bool ColorArea::isNeedDrawFrame() const
{
    return mNeedDrawFrame;
}

void ColorArea::setNeedDrawFrame(const bool &aNeedDrawFrame)
{
    if (mNeedDrawFrame!=aNeedDrawFrame)
    {
        mNeedDrawFrame=aNeedDrawFrame;
        update();
    }
}

bool ColorArea::isSelected() const
{
    return mSelected;
}

void ColorArea::setSelected(const bool &aSelected)
{
    if (mSelected!=aSelected)
    {
        mSelected=aSelected;
        update();
    }
}

bool ColorArea::isSelectAllowed() const
{
    return mSelectAllowed;
}

void ColorArea::setSelectAllowed(const bool &aSelectAllowed)
{
    mSelectAllowed=aSelectAllowed;
}

bool ColorArea::isPopupAllowed() const
{
    return mPopupAllowed;
}

void ColorArea::setPopupAllowed(const bool &aPopupAllowed)
{
    mPopupAllowed=aPopupAllowed;
}

quint8 ColorArea::popupCount() const
{
    return mPopupCount;
}

void ColorArea::setPopupCount(const quint8 &aPopupCount)
{
    mPopupCount=aPopupCount;
}

quint8 ColorArea::popupCellSize() const
{
    return mPopupCellSize;
}

void ColorArea::setPopupCellSize(const quint8 &aPopupCellSize)
{
    mPopupCellSize=aPopupCellSize;
}
