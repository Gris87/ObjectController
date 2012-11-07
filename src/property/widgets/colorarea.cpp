#include "colorarea.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QGridLayout>
#include <QPainter>

ColorArea::ColorArea(QWidget *parent) :
    QFrame(parent)
{
    QSizePolicy aPolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(aPolicy);

    setFrameShadow(QFrame::Sunken);
    setFrameShape(QFrame::StyledPanel);

    mColor.setRgb(0, 0, 0);

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
            QColorDialog dialog(color(), this);

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
    int aWidth=width();
    int aHeight=height();

    QPainter paint(this);

    if (mColor.alpha()<255)
    {
        int aCurRow=0;

        while ((aCurRow<<3)<aHeight)
        {
            int aCurCol=0;

            while ((aCurCol<<3)<aWidth)
            {
                if ((aCurRow + aCurCol) & 1)
                {
                    paint.fillRect(aCurCol<<3, aCurRow<<3, 8, 8, QBrush(QColor(255, 255, 255)));
                }
                else
                {
                    paint.fillRect(aCurCol<<3, aCurRow<<3, 8, 8, QBrush(QColor(0, 0, 0)));
                }

                ++aCurCol;
            }

            ++aCurRow;
        }
    }

    paint.fillRect(0, 0, aWidth, aHeight, QBrush(mColor));

    if (mNeedDrawFrame)
    {
        drawFrame(&paint);
    }
}

void ColorArea::cellClicked()
{
    ColorArea *aArea=(ColorArea *)sender();

    setColor(aArea->color());

    delete mPopupWidget;
    mPopupWidget=0;
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
