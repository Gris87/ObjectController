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

    mFont=QFont("Courier new", 1);     // Special action to calculate mCharWidth and mCharHeight at the next step
    setFont(QFont("Courier new", 10));

    mSelectionStart=0;
    mSelectionEnd=0;
    mSelectionInit=0;

    mCursorVisible=true;
    mCursorAtTheLeft=true;
    connect(&mCursorTimer, SIGNAL(timeout()), this, SLOT(cursorBlicking()));
    mCursorTimer.start(500);

    mLeftButtonPressed=false;
    mOneMoreSelection=false;
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

void BitEditor::copy()
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
        aCurSize*=10;
    }

    if (mAddressWidth==0)
    {
        mAddressWidth=1;
    }

    mLinesCount=floor(aDataSize/8.0f);

    if (aDataSize % 8!=0)
    {
        ++mLinesCount;
    }



    int aTotalWidth=(mAddressWidth+12)*mCharWidth; // mAddressWidth + 1+8+1 + 1+1
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
    bool aSelectionChanged=(mSelectionStart!=mCursorPosition) || (mSelectionEnd!=mCursorPosition);

    mSelectionInit=mCursorPosition;
    mSelectionStart=mCursorPosition;
    mSelectionEnd=mCursorPosition;

    if (aSelectionChanged)
    {
        viewport()->update();
        emit selectionChanged(mSelectionStart, mSelectionEnd);
    }
}

void BitEditor::updateSelection()
{
    bool aSelectionChanged=false;

    if (mCursorPosition<mSelectionInit)
    {
        if (mSelectionStart!=mCursorPosition || mSelectionEnd!=mSelectionInit+(mOneMoreSelection ? 1 : 0))
        {
            mSelectionStart=mCursorPosition;
            mSelectionEnd=mSelectionInit+(mOneMoreSelection ? 1 : 0);

            aSelectionChanged=true;

            mOneMoreSelection=false;
        }
    }
    else
    {
        if (mSelectionStart!=mSelectionInit || mSelectionEnd!=mCursorPosition)
        {
            mSelectionStart=mSelectionInit;
            mSelectionEnd=mCursorPosition;

            aSelectionChanged=true;
        }
    }

    if (aSelectionChanged)
    {
        viewport()->update();
        emit selectionChanged(mSelectionStart, mSelectionEnd);
    }
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
    QPainter painter(viewport());
    QPalette aPalette=palette();

    QColor aTextColor=aPalette.color(QPalette::Text);
    QColor aHighlightColor=aPalette.color(QPalette::Highlight);
    QColor aHighlightedTextColor=aPalette.color(QPalette::HighlightedText);
    QColor aAlternateBaseColor=aPalette.color(QPalette::AlternateBase);

    int aOffsetX=-horizontalScrollBar()->value();
    int aOffsetY=-verticalScrollBar()->value();
    int aViewWidth=viewport()->width();
    int aViewHeight=viewport()->height();

    painter.setFont(mFont);

    // Draw background for chars (Selection and cursor)
    {
        // Check for selection
        if (mSelectionStart!=mSelectionEnd)
        {
            // Draw selection
            int aStartRow=floor(mSelectionStart/8.0f);
            int aStartCol=mSelectionStart % 8;

            int aEndRow=floor((mSelectionEnd-1)/8.0f);
            int aEndCol=(mSelectionEnd-1) % 8;

            int aRightX=(mAddressWidth+11)*mCharWidth+aOffsetX;              // mAddressWidth + 1+8+1 + 1

            int aStartLeftX=(mAddressWidth+1+aStartCol)*mCharWidth+aOffsetX; // mAddressWidth + 1+aStartCol
            int aStartY=aStartRow*(mCharHeight+LINE_INTERVAL)+aOffsetY;

            int aEndLeftX=(mAddressWidth+1+aEndCol)*mCharWidth+aOffsetX;     // mAddressWidth + 1+aEndCol
            int aEndY=aEndRow*(mCharHeight+LINE_INTERVAL)+aOffsetY;

            if (aStartRow==aEndRow)
            {
                painter.fillRect(aStartLeftX, aStartY, aEndLeftX-aStartLeftX+mCharWidth,    mCharHeight, aHighlightColor);
                painter.fillRect(aRightX, aStartY, mCharWidth, mCharHeight, aHighlightColor);
            }
            else
            {
                QRect aBitRect(
                               mAddressWidth*mCharWidth+aOffsetX,
                               (aStartRow+1)*(mCharHeight+LINE_INTERVAL)-LINE_INTERVAL+aOffsetY,
                               10*mCharWidth,
                               (aEndRow-aStartRow-1)*(mCharHeight+LINE_INTERVAL)+LINE_INTERVAL
                              );

                if (aEndRow>aStartRow+1)
                {
                    painter.fillRect(aBitRect,  aHighlightColor);
                }

                painter.fillRect(aStartLeftX, aStartY, aBitRect.right()-aStartLeftX+1, mCharHeight, aHighlightColor);
                painter.fillRect(aBitRect.left(), aEndY-LINE_INTERVAL, aEndLeftX-aBitRect.left()+mCharWidth, mCharHeight+LINE_INTERVAL, aHighlightColor);

                painter.fillRect(aRightX, aStartY, mCharWidth, aEndY-aStartY+mCharHeight, aHighlightColor);
            }
        }
        else
        {
            // Draw cursor
            int aCurRow=floor(mCursorPosition/8.0f);
            int aCursorY=aCurRow*(mCharHeight+LINE_INTERVAL)+aOffsetY;

            if (aCursorY+mCharHeight>=0 && aCursorY<=aViewHeight)
            {
                int aCurCol=mCursorPosition % 8;
                int aCursorX=(mAddressWidth+1+aCurCol)*mCharWidth+aOffsetX; // mAddressWidth +1+aCurCol

                if (
                    (
                     !mCursorAtTheLeft
                     ||
                     mCursorVisible
                    )
                    &&
                    (
                     aCursorX>=(mAddressWidth-1)*mCharWidth
                     &&
                     aCursorX<=aViewWidth
                    )
                   )
                {
                    if (mMode==INSERT)
                    {
                        painter.fillRect(aCursorX, aCursorY+mCharHeight, mCharWidth, LINE_INTERVAL, aHighlightColor);
                    }
                    else
                    {
                        painter.fillRect(aCursorX, aCursorY, mCharWidth, mCharHeight, aHighlightColor);
                    }
                }

                aCursorX=(mAddressWidth+11)*mCharWidth+aOffsetX; // mAddressWidth +1+8+1 +1

                if (
                    (
                     mCursorAtTheLeft
                     ||
                     mCursorVisible
                    )
                    &&
                    (
                     aCursorX>=(mAddressWidth-1)*mCharWidth
                     &&
                     aCursorX<=aViewWidth
                    )
                   )
                {
                    if (mMode==INSERT)
                    {
                        painter.fillRect(aCursorX, aCursorY+mCharHeight, mCharWidth, LINE_INTERVAL, aHighlightColor);
                    }
                    else
                    {
                        painter.fillRect(aCursorX, aCursorY, mCharWidth, mCharHeight, aHighlightColor);
                    }
                }
            }
        }
    }

    // Bit data and ASCII characters
    {
        int aDataSize=mData.size();
        int aCurRow=0;
        int aCurCol=0;

        for (int i=0; i<aDataSize; ++i)
        {
            int aCharY=aCurRow*(mCharHeight+LINE_INTERVAL)+aOffsetY;

            if (aCharY+mCharHeight<0)
            {
                i+=7;
                ++aCurRow;
                continue;
            }
            else
            if (aCharY>aViewHeight)
            {
                break;
            }

            // -----------------------------------------------------------------------------------------------------------------

            int aCharX=(mAddressWidth+1+aCurCol)*mCharWidth+aOffsetX; // mAddressWidth + 1+aCurCol

            if (aCharX>=(mAddressWidth-1)*mCharWidth && aCharX<=aViewWidth)
            {
                if (i>=mSelectionStart && i<mSelectionEnd)
                {
                    painter.setPen(aHighlightedTextColor);
                }
                else
                {
                    painter.setPen(aTextColor);
                }

                if (i==mSelectionStart && i==mSelectionEnd && mMode==OVERWRITE)
                {
                    if (mCursorAtTheLeft && !mCursorVisible)
                    {
                        painter.setPen(aTextColor);
                    }
                    else
                    {
                        painter.setPen(aHighlightedTextColor);
                    }
                }

                painter.drawText(aCharX, aCharY, mCharWidth, mCharHeight, Qt::AlignCenter, mData.at(i) ? "1" : "0");
            }

            // -----------------------------------------------------------------------------------------------------------------

            if (aCurCol==7 || i==aDataSize-1)
            {
                aCharX=(mAddressWidth+11)*mCharWidth+aOffsetX; // mAddressWidth + 1+8+1 + 1

                if (aCharX>=(mAddressWidth-1)*mCharWidth && aCharX<=aViewWidth)
                {
                    int aStartRow=floor(mSelectionStart/8.0f);
                    int aEndRow=floor((mSelectionEnd-(mSelectionStart==mSelectionEnd? 0 : 1))/8.0f);

                    if (
                        aCurRow>=aStartRow
                        &&
                        aCurRow<=aEndRow
                        &&
                        (
                         mSelectionStart!=mSelectionEnd
                         ||
                         (
                          mMode==OVERWRITE
                          &&
                          (
                           mCursorAtTheLeft
                           ||
                           mCursorVisible
                          )
                         )
                        )
                       )
                    {
                        painter.setPen(aHighlightedTextColor);
                    }
                    else
                    {
                        painter.setPen(aTextColor);
                    }

                    quint8 aAsciiChar=0;

                    for (int j=0; j<=aCurCol; ++j)
                    {
                        aAsciiChar<<=1;

                        if (mData.at(i-aCurCol+j))
                        {
                            aAsciiChar|=1;
                        }
                    }

                    painter.drawText(aCharX, aCharY, mCharWidth, mCharHeight, Qt::AlignCenter, mAsciiChars.at(aAsciiChar));
                }
            }

            // -----------------------------------------------------------------------------------------------------------------

            ++aCurCol;

            if (aCurCol==8)
            {
                ++aCurRow;
                aCurCol=0;
            }
        }
    }

    // Line delimeters
    {
        painter.setPen(QColor(0, 0, 0));

        int aLineX;

        aLineX=mAddressWidth*mCharWidth;
        painter.drawLine(aLineX, 0, aLineX, aViewHeight);

        aLineX=(mAddressWidth+10)*mCharWidth+aOffsetX; // mAddressWidth + 1+8+1
        painter.drawLine(aLineX, 0, aLineX, aViewHeight);
    }

    // Address field at the left side
    {
        painter.setPen(aTextColor);
        painter.fillRect(0, 0, mAddressWidth*mCharWidth, aViewHeight, aAlternateBaseColor);

        for (int i=0; i<mLinesCount; ++i)
        {
            int aCharY=i*(mCharHeight+LINE_INTERVAL)+aOffsetY;

            if (aCharY+mCharHeight<0)
            {
                continue;
            }
            else
            if (aCharY>aViewHeight)
            {
                break;
            }



            QString aBitAddress=QString::number(i*8);

            for (int j=0; j<mAddressWidth; ++j)
            {
                int aCharX=j*mCharWidth;

                if (aCharX>aViewWidth)
                {
                    break;
                }

                QChar aBitChar;

                if (mAddressWidth-j-1<aBitAddress.length())
                {
                    aBitChar=aBitAddress.at(aBitAddress.length()-mAddressWidth+j);
                }
                else
                {
                    aBitChar='0';
                }

                painter.drawText(aCharX, aCharY, mCharWidth, mCharHeight, Qt::AlignCenter, aBitChar);
            }
        }
    }
}

void BitEditor::keyPressEvent(QKeyEvent *event)
{
    // =======================================================================================
    //                                     Movements
    // =======================================================================================
    if (event->matches(QKeySequence::MoveToPreviousChar))
    {
        if (mCursorAtTheLeft)
        {
            setCursorPosition(mCursorPosition-1);
        }
        else
        {
            setPosition(position()-1);
        }

        cursorMoved(false);
    }
    else
    if (event->matches(QKeySequence::MoveToNextChar))
    {
        if (mCursorAtTheLeft)
        {
            setCursorPosition(mCursorPosition+1);
        }
        else
        {
            setPosition(position()+1);
        }

        cursorMoved(false);
    }
    else
    if (event->matches(QKeySequence::MoveToPreviousLine))
    {
        setCursorPosition(mCursorPosition-8);
        cursorMoved(false);
    }
    else
    if (event->matches(QKeySequence::MoveToNextLine))
    {
        setCursorPosition(mCursorPosition+8);
        cursorMoved(false);
    }
    else
    if (event->matches(QKeySequence::MoveToStartOfLine))
    {
        setCursorPosition(mCursorPosition-(mCursorPosition % 8));
        cursorMoved(false);
    }
    else
    if (event->matches(QKeySequence::MoveToEndOfLine))
    {
        setCursorPosition(mCursorPosition | 7);
        cursorMoved(false);
    }
    else
    if (event->matches(QKeySequence::MoveToPreviousPage))
    {
        setCursorPosition(mCursorPosition-viewport()->height()/(mCharHeight+LINE_INTERVAL)*8);
        cursorMoved(false);
    }
    else
    if (event->matches(QKeySequence::MoveToNextPage))
    {
        setCursorPosition(mCursorPosition+viewport()->height()/(mCharHeight+LINE_INTERVAL)*8);
        cursorMoved(false);
    }
    else
    if (event->matches(QKeySequence::MoveToStartOfDocument))
    {
        setCursorPosition(0);
        cursorMoved(false);
    }
    else
    if (event->matches(QKeySequence::MoveToEndOfDocument))
    {
        setCursorPosition(mData.size());
        cursorMoved(false);
    }
    // =======================================================================================
    //                                     Selecting
    // =======================================================================================
    else
    if (event->matches(QKeySequence::SelectAll))
    {
        mSelectionInit=0;
        setCursorPosition(mData.size());
        cursorMoved(true);
    }
    else
    if (event->matches(QKeySequence::SelectPreviousChar))
    {
        if (mCursorAtTheLeft)
        {
            setCursorPosition(mCursorPosition-1);
        }
        else
        {
            setPosition(position()-1);
        }

        cursorMoved(true);
    }
    else
    if (event->matches(QKeySequence::SelectNextChar))
    {
        if (mCursorAtTheLeft)
        {
            setCursorPosition(mCursorPosition+1);
        }
        else
        {
            setPosition(position()+1);
        }

        cursorMoved(true);
    }
    else
    if (event->matches(QKeySequence::SelectPreviousLine))
    {
        setCursorPosition(mCursorPosition-8);
        cursorMoved(true);
    }
    else
    if (event->matches(QKeySequence::SelectNextLine))
    {
        setCursorPosition(mCursorPosition+8);
        cursorMoved(true);
    }
    else
    if (event->matches(QKeySequence::SelectStartOfLine))
    {
        setCursorPosition(mCursorPosition-(mCursorPosition % 8));
        cursorMoved(true);
    }
    else
    if (event->matches(QKeySequence::SelectEndOfLine))
    {
        setCursorPosition(mCursorPosition | 7);
        cursorMoved(true);
    }
    else
    if (event->matches(QKeySequence::SelectPreviousPage))
    {
        setCursorPosition(mCursorPosition-viewport()->height()/(mCharHeight+LINE_INTERVAL)*8);
        cursorMoved(true);
    }
    else
    if (event->matches(QKeySequence::SelectNextPage))
    {
        setCursorPosition(mCursorPosition+viewport()->height()/(mCharHeight+LINE_INTERVAL)*8);
        cursorMoved(true);
    }
    else
    if (event->matches(QKeySequence::SelectStartOfDocument))
    {
        setCursorPosition(0);
        cursorMoved(true);
    }
    else
    if (event->matches(QKeySequence::SelectEndOfDocument))
    {
        setCursorPosition(mData.size());
        cursorMoved(true);
    }
    // =======================================================================================
    //                                      Others
    // =======================================================================================
    else
    if (event->matches(QKeySequence::Copy))
    {
        copy();
    }
    else
    if ((event->key() == Qt::Key_Tab) && (event->modifiers() == Qt::NoModifier))
    {
        mCursorAtTheLeft=!mCursorAtTheLeft;
        cursorMoved(true);
    }
    else
    if ((event->key() == Qt::Key_Insert) && (event->modifiers() == Qt::NoModifier))
    {
        if (mMode==INSERT)
        {
            setMode(OVERWRITE);
        }
        else
        {
            setMode(INSERT);
        }
    }
    // =======================================================================================
    //                                     Editing
    // =======================================================================================
    else
    if (!mReadOnly)
    {

    }
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
    mLeftButtonPressed=false;

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
    return mCursorPosition>>3;
}

void BitEditor::setPosition(int aPosition)
{
    if ((mCursorPosition>>3)!=aPosition)
    {
        setCursorPosition(aPosition<<3);
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
    if (aCursorPos>mData.size())
    {
        aCursorPos=mData.size();
    }

    if (mCursorPosition!=aCursorPos)
    {
        mCursorPosition=aCursorPos;
        viewport()->update();

        emit positionChanged(mCursorPosition);
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
