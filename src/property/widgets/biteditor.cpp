#include "biteditor.h"

#include <QPainter>
#include <QScrollBar>
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>

#include <math.h>

#define LINE_INTERVAL 2
#define CHAR_INTERVAL 2

BitEditor::BitEditor(QWidget *parent) :
    QAbstractScrollArea(parent)
{
    for (int i=0; i<256; ++i)
    {
        char aChar=i;
        mAsciiChars.append(QString::fromLatin1(&aChar, 1));
    }

    mAsciiChars[9] =QChar(26);
    mAsciiChars[10]=QChar(8629);
    mAsciiChars[13]=QChar(8601);
    mAsciiChars[32]=QChar(183);

    for (int i=128; i<=160; ++i)
    {
        mAsciiChars[i]=QChar(9734);
    }



    mMode=INSERT;
    mReadOnly=false;
    mCursorPosition=0;

    mFont=QFont("Courier new", 1);     //Special action to calculate mCharWidth and mCharHeight at the next step
    setFont(QFont("Courier new", 10));

    mSelectionStart=0;
    mSelectionEnd=0;
    mSelectionInit=0;

    mCursorVisible=true;
    mCursorAtTheLeft=true;
    connect(&mCursorTimer, SIGNAL(timeout()), this, SLOT(cursorBlicking()));
    mCursorTimer.start(500);
}

void BitEditor::undo()
{
    mUndoStack.undo();
    emit dataChanged();

    setCursorPosition(mCursorPosition);
    cursorMoved(false);

    updateScrollBars();
    viewport()->update();
}

void BitEditor::redo()
{
    mUndoStack.redo();
    emit dataChanged();

    setCursorPosition(mCursorPosition);
    cursorMoved(false);

    updateScrollBars();
    viewport()->update();
}

void BitEditor::cursorBlicking()
{
    mCursorVisible=!mCursorVisible;
    viewport()->update();
}

void BitEditor::scrollToCursor()
{

}

// ------------------------------------------------------------------

void BitEditor::updateScrollBars()
{
    mAddressWidth=0;
    int aDataSize=mData.size();
    int aCurSize=1;

    while (aCurSize<aDataSize)
    {
        ++mAddressWidth;
        aCurSize<<=4;
    }

    if (mAddressWidth==0)
    {
        ++mAddressWidth;
    }

    mLinesCount=floor(aDataSize/8.0f);

    if (aDataSize % 8!=0)
    {
        ++mLinesCount;
    }



    int aTotalWidth=(mAddressWidth+13)*mCharWidth; // mAddressWidth + 1+8+1 + 1
    int aTotalHeight=mLinesCount*mCharHeight;

    if (mLinesCount>0)
    {
        aTotalHeight+=(mLinesCount-1)*LINE_INTERVAL;
    }



    QSize areaSize=viewport()->size();

    horizontalScrollBar()->setPageStep(areaSize.width());
    verticalScrollBar()->setPageStep(areaSize.height());

    horizontalScrollBar()->setRange(0, aTotalWidth  - areaSize.width()  + 1);
    verticalScrollBar()->setRange(  0, aTotalHeight - areaSize.height() + 1);
}

void BitEditor::resetCursorTimer()
{
    mCursorVisible=true;

    mCursorTimer.stop();
    mCursorTimer.start(500);

    viewport()->update();
}

void BitEditor::resetSelection()
{
}

void BitEditor::updateSelection()
{
}

void BitEditor::cursorMoved(bool aKeepSelection)
{
    if (aKeepSelection)
    {
        updateSelection();
    }
    else
    {
        resetSelection();
    }

    resetCursorTimer();
    scrollToCursor();
}

void BitEditor::resizeEvent(QResizeEvent *event)
{
    QAbstractScrollArea::resizeEvent(event);
    updateScrollBars();
}

void BitEditor::paintEvent(QPaintEvent */*event*/)
{

}

void BitEditor::keyPressEvent(QKeyEvent *event)
{

}

void BitEditor::mousePressEvent(QMouseEvent *event)
{
    /*
    mLeftButtonPressed=(event->button()==Qt::LeftButton);

    if (mLeftButtonPressed)
    {
        bool aShift=event->modifiers() & Qt::ShiftModifier;
        int aPosition=charAt(event->pos(), &mCursorAtTheLeft);

        if (aShift)
        {
            if ((aPosition>>1)>=mSelectionInit)
            {
                aPosition+=2;
            }
            else
            {
                mOneMoreSelection=true;
            }
        }

        setCursorPosition(aPosition);
        cursorMoved(aShift);
    }
    */

    QAbstractScrollArea::mousePressEvent(event);
}

void BitEditor::mouseMoveEvent(QMouseEvent *event)
{
    /*
    if (mLeftButtonPressed)
    {
        int aPosition=charAt(event->pos(), &mCursorAtTheLeft);

        if ((aPosition>>1)>=mSelectionInit)
        {
            aPosition+=2;
        }
        else
        {
            mOneMoreSelection=true;
        }

        setCursorPosition(aPosition);
        cursorMoved(true);
    }
    */

    QAbstractScrollArea::mouseMoveEvent(event);
}

void BitEditor::mouseReleaseEvent(QMouseEvent *event)
{
    /*
    mLeftButtonPressed=false;
    */

    QAbstractScrollArea::mouseReleaseEvent(event);
}

void BitEditor::wheelEvent(QWheelEvent *event)
{
    if (event->delta()>=0)
    {
        verticalScrollBar()->setValue(verticalScrollBar()->value()-10*(mCharHeight+LINE_INTERVAL));
    }
    else
    {
        verticalScrollBar()->setValue(verticalScrollBar()->value()+10*(mCharHeight+LINE_INTERVAL));
    }
}

// ------------------------------------------------------------------

QBitArray BitEditor::data() const
{
    return mData;
}

void BitEditor::setData(QBitArray const &aData)
{
    if (mData!=aData)
    {
        mData=aData;
        setCursorPosition(mCursorPosition);
        mUndoStack.clear();

        updateScrollBars();
        viewport()->update();

        emit dataChanged();
    }
}

BitEditor::Mode BitEditor::mode() const
{
    return mMode;
}

void BitEditor::setMode(const Mode &aMode)
{
    if (mMode!=aMode)
    {
        mMode=aMode;

        resetCursorTimer();

        emit modeChanged(mMode);
    }
}

bool BitEditor::isReadOnly() const
{
    return mReadOnly;
}

void BitEditor::setReadOnly(const bool &aReadOnly)
{
    mReadOnly=aReadOnly;
}

int BitEditor::position() const
{
    return mCursorPosition>>1;
}

void BitEditor::setPosition(int aPosition)
{
    if ((mCursorPosition>>1)!=aPosition)
    {
        setCursorPosition(aPosition<<1);
    }
}

qint64 BitEditor::cursorPosition() const
{
    return mCursorPosition;
}

void BitEditor::setCursorPosition(qint64 aCursorPos)
{
    if (aCursorPos<0)
    {
        aCursorPos=0;
    }
    else
    if (aCursorPos>mData.size()<<1)
    {
        aCursorPos=mData.size()<<1;
    }

    if (mCursorPosition!=aCursorPos)
    {
        bool aSamePos=((mCursorPosition>>1)==(aCursorPos>>1));

        mCursorPosition=aCursorPos;
        viewport()->update();

        if (!aSamePos)
        {
            emit positionChanged(mCursorPosition>>1);
        }
    }
}

QFont BitEditor::font() const
{
    return mFont;
}

void BitEditor::setFont(const QFont &aFont)
{
    if (mFont!=aFont)
    {
        mFont=aFont;

        QFontMetrics aFontMetrics(mFont);

        int aCharWidth1=aFontMetrics.width('0');
        int aCharWidth2=aFontMetrics.width('1');

        if (aCharWidth1>aCharWidth2)
        {
            mCharWidth=aCharWidth1;
        }
        else
        {
            mCharWidth=aCharWidth2;
        }

        mCharWidth+=CHAR_INTERVAL;
        mCharHeight=aFontMetrics.height()+CHAR_INTERVAL;

        updateScrollBars();
        viewport()->update();
    }
}

int BitEditor::charWidth()
{
    return mCharWidth;
}

int BitEditor::charHeight()
{
    return mCharHeight;
}

quint8 BitEditor::addressWidth()
{
    return mAddressWidth;
}

int BitEditor::linesCount()
{
    return mLinesCount;
}

int BitEditor::selectionStart()
{
    return mSelectionStart;
}

int BitEditor::selectionEnd()
{
    return mSelectionEnd;
}

bool BitEditor::isCursorAtTheLeft()
{
    return mCursorAtTheLeft;
}
