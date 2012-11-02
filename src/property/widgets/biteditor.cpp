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
    int aOffsetX=horizontalScrollBar()->value();
    int aOffsetY=verticalScrollBar()->value();
    int aViewWidth=viewport()->width();
    int aViewHeight=viewport()->height();



    int aCurCol=mCursorPosition & 7;
    int aCurRow=mCursorPosition>>3;

    int aCursorX;
    int aCursorY=aCurRow*(mCharHeight+LINE_INTERVAL);

    if (mCursorAtTheLeft)
    {
        aCursorX=(mAddressWidth+1+aCurCol)*mCharWidth; // mAddressWidth + 1+aCurCol
    }
    else
    {
        aCursorX=(mAddressWidth+11)*mCharWidth;        // mAddressWidth +1+8+1 +1
    }



    if (aCursorX-mAddressWidth*mCharWidth<aOffsetX)
    {
        horizontalScrollBar()->setValue(aCursorX-mAddressWidth*mCharWidth);
    }
    else
    if (aCursorX+mCharWidth>aOffsetX+aViewWidth)
    {
        horizontalScrollBar()->setValue(aCursorX+mCharWidth-aViewWidth);
    }

    if (aCursorY<aOffsetY)
    {
        verticalScrollBar()->setValue(aCursorY);
    }
    else
    if (aCursorY+mCharHeight+LINE_INTERVAL>aOffsetY+aViewHeight)
    {
        verticalScrollBar()->setValue(aCursorY+mCharHeight+LINE_INTERVAL-aViewHeight);
    }
}

int BitEditor::charAt(QPoint aPos, bool *aAtLeftPart)
{
    int aOffsetX=horizontalScrollBar()->value();
    int aOffsetY=verticalScrollBar()->value();

    int aRow         = floor((aPos.y()+aOffsetY)/((double)(mCharHeight+LINE_INTERVAL)));
    int aLeftColumn  = (int)floor((aPos.x()+aOffsetX-(mAddressWidth+1)*mCharWidth)/((double)mCharWidth));
    int aRightColumn = floor((aPos.x()+aOffsetX-(mAddressWidth+11)*mCharWidth)/((double)mCharWidth));

    if (aAtLeftPart)
    {
        *aAtLeftPart=true;
    }

    if (aLeftColumn<0)
    {
        return aRow*8;
    }
    else
    if (aLeftColumn>=8)
    {
        if (aAtLeftPart)
        {
            *aAtLeftPart=false;
        }

        if (aRightColumn<0)
        {
            return aRow*8;
        }
        else
        if (aRightColumn>=1)
        {
            return aRow*8+7;
        }

        return aRow*8;
    }
    else
    {
        return aRow*8+aLeftColumn;
    }
}

int BitEditor::indexOf(const QBitArray &aArray, int aFrom) const
{
    if (aFrom<0)
    {
        aFrom=0;
    }

    for (int i=aFrom; i<=mData.size()-aArray.size(); ++i)
    {
        bool good=true;

        for (int j=0; j<aArray.size(); ++j)
        {
            if (mData.at(i+j)!=aArray.at(j))
            {
                good=false;
                break;
            }
        }

        if (good)
        {
            return i;
        }
    }

    return -1;
}

int BitEditor::indexOf(const bool &aBool, int aFrom) const
{
    QBitArray aArray;
    aArray.resize(1);
    aArray.setBit(0, aBool);
    return indexOf(aArray, aFrom);
}

int BitEditor::lastIndexOf(const QBitArray &aArray, int aFrom) const
{
    if (aFrom<=0 || aFrom>mData.size()-aArray.size())
    {
        aFrom=mData.size()-aArray.size();
    }

    for (int i=aFrom; i>=0; --i)
    {
        bool good=true;

        for (int j=0; j<aArray.size(); ++j)
        {
            if (mData.at(i+j)!=aArray.at(j))
            {
                good=false;
                break;
            }
        }

        if (good)
        {
            return i;
        }
    }

    return -1;
}

int BitEditor::lastIndexOf(const bool &aBool, int aFrom) const
{
    QBitArray aArray;
    aArray.resize(1);
    aArray.setBit(0, aBool);
    return indexOf(aArray, aFrom);
}

void BitEditor::insert(int aIndex, bool aBool)
{
    QBitArray aArray;
    aArray.resize(1);
    aArray.setBit(0, aBool);
    insert(aIndex, aArray);
}

void BitEditor::insert(int aIndex, const QBitArray &aArray)
{
    if (aArray.size()==0)
    {
        return;
    }

    MultipleBitUndoCommand *aCommand;

    if (mMode==INSERT)
    {
        aCommand=new MultipleBitUndoCommand(this, MultipleBitUndoCommand::Insert, aIndex, aArray.size(), aArray);
    }
    else
    {
        aCommand=new MultipleBitUndoCommand(this, MultipleBitUndoCommand::Replace, aIndex, aArray.size(), aArray);
    }

    mUndoStack.push(aCommand);
    emit dataChanged();

    setCursorPosition(mCursorPosition);
    resetSelection();

    updateScrollBars();
    viewport()->update();
}

void BitEditor::remove(int aPos, int aLength)
{
    if (aLength<=0)
    {
        return;
    }

    QUndoCommand *aCommand;

    if (mMode==INSERT)
    {
        aCommand=new MultipleBitUndoCommand(this, MultipleBitUndoCommand::Remove, aPos, aLength);
    }
    else
    {
        QBitArray aArray=QBitArray(aLength, 0);
        aCommand=new MultipleBitUndoCommand(this, MultipleBitUndoCommand::Replace, aPos, aLength, aArray);
    }

    mUndoStack.push(aCommand);
    emit dataChanged();

    setCursorPosition(mCursorPosition);
    resetSelection();

    updateScrollBars();
    viewport()->update();
}

void BitEditor::replace(int aPos, bool aBool)
{
    QBitArray aArray;
    aArray.resize(1);
    aArray.setBit(0, aBool);
    replace(aPos, aArray);
}

void BitEditor::replace(int aPos, const QBitArray &aArray)
{
    replace(aPos, aArray.size(), aArray);
}

void BitEditor::replace(int aPos, int aLength, const QBitArray &aArray)
{
    MultipleBitUndoCommand *aCommand=new MultipleBitUndoCommand(this, MultipleBitUndoCommand::Replace, aPos, aLength, aArray);
    mUndoStack.push(aCommand);
    emit dataChanged();

    setCursorPosition(mCursorPosition);
    resetSelection();

    updateScrollBars();
    viewport()->update();
}

void BitEditor::setSelection(int aPos, int aCount)
{
    if (aCount<0)
    {
        aCount=0;
    }

    qint64 aPrevPos=mCursorPosition;

    mCursorPosition=aPos;
    resetSelection();

    mCursorPosition+=aCount;
    updateSelection();

    mCursorPosition=aPrevPos;
}

void BitEditor::cut()
{
    copy();

    if (mCursorAtTheLeft)
    {
        if (mSelectionStart==mSelectionEnd)
        {
            remove(mSelectionStart, 1);
        }
        else
        {
            remove(mSelectionStart, mSelectionEnd-mSelectionStart);
        }
    }
    else
    {
        int aStartRow=mSelectionStart>>3;
        mSelectionStart=aStartRow<<3;

        if ((mSelectionEnd & 7)!=0)
        {
            int aEndRow=mSelectionEnd>>3;
            mSelectionEnd=(aEndRow<<3)+8;
        }

        if (mSelectionStart==mSelectionEnd)
        {
            mSelectionEnd+=8;
        }

        remove(mSelectionStart, mSelectionEnd-mSelectionStart);
    }

    setCursorPosition(mSelectionStart);
    cursorMoved(false);
}

void BitEditor::copy()
{
    QString aToClipboard;

    if (mCursorAtTheLeft)
    {
        if (mSelectionStart==mSelectionEnd)
        {
            if (mSelectionStart<mData.size())
            {
                bool aBool=mData.at(mSelectionStart);
                aToClipboard=aBool? "1" : "0";
            }
        }
        else
        {
            for (int i=mSelectionStart; i<mSelectionEnd && i<mData.size(); ++i)
            {
                bool aBool=mData.at(i);
                QString aBitChar=aBool? "1" : "0";

                aToClipboard.append(aBitChar);
            }
        }
    }
    else
    {
        int aStartRow=mSelectionStart>>3;
        int aSelectionStart=aStartRow<<3;
        int aSelectionEnd=mSelectionEnd;

        if ((aSelectionEnd & 7)!=0)
        {
            int aEndRow=aSelectionEnd>>3;
            aSelectionEnd=(aEndRow<<3)+8;
        }

        if (aSelectionStart==aSelectionEnd)
        {
            aSelectionEnd+=8;
        }

        for (int i=aSelectionStart; i<aSelectionEnd && i<mData.size(); i+=8)
        {
            char aChar=0;

            for (int j=0; j<=7; ++j)
            {
                if (i+j>=mData.size())
                {
                    break;
                }

                aChar<<=1;

                if (mData.at(i+j))
                {
                    aChar|=1;
                }
            }

            aToClipboard.append(QString::fromLatin1(&aChar, 1));
        }
    }

    QApplication::clipboard()->setText(aToClipboard);
}

void BitEditor::paste()
{
    // TODO: Implement paste
}

QString BitEditor::toString()
{
    QString res="";

    for (int i=0; i<mData.size(); i+=8)
    {
        char aChar=0;

        for (int j=0; j<=7; ++j)
        {
            if (i+j>=mData.size())
            {
                break;
            }

            aChar<<=1;

            if (mData.at(i+j))
            {
                aChar|=1;
            }
        }

        res.append(QString::fromLatin1(&aChar, 1));
    }

    return res;
}

// ------------------------------------------------------------------

void BitEditor::updateScrollBars()
{
    mAddressWidth=0;
    int aDataSize=mData.size();
    int aCurSize=1;

    while (aCurSize<=aDataSize)
    {
        ++mAddressWidth;
        aCurSize*=10;
    }

    if (mAddressWidth==0)
    {
        mAddressWidth=1;
    }

    mLinesCount=(aDataSize>>3)+1;



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

void BitEditor::paintEvent(QPaintEvent * /*event*/)
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
            int aStartRow=mSelectionStart>>3;
            int aStartCol=mSelectionStart & 7;

            int aEndRow=(mSelectionEnd-1)>>3;
            int aEndCol=(mSelectionEnd-1) & 7;

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
            int aCurRow=mCursorPosition>>3;
            int aCursorY=aCurRow*(mCharHeight+LINE_INTERVAL)+aOffsetY;

            if (aCursorY+mCharHeight>=0 && aCursorY<=aViewHeight)
            {
                int aCurCol=mCursorPosition & 7;
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
                    int aStartRow=mSelectionStart>>3;
                    int aEndRow=(mSelectionEnd-(mSelectionStart==mSelectionEnd? 0 : 1))>>3;

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
        setCursorPosition(mCursorPosition-(mCursorPosition & 7));
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
        setCursorPosition(mCursorPosition-(mCursorPosition & 7));
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
        if (event->matches(QKeySequence::Undo))
        {
            undo();
        }
        else
        if (event->matches(QKeySequence::Redo))
        {
            redo();
        }
        else
        if (event->matches(QKeySequence::Delete))
        {
            int aSelStart=mSelectionStart;

            if (mCursorAtTheLeft)
            {
                if (mSelectionStart==mSelectionEnd)
                {
                    if (mSelectionStart<mData.size())
                    {
                        if (mMode==INSERT)
                        {
                            remove(mSelectionStart, 1);
                        }
                        else
                        {
                            replace(mSelectionStart, 0);
                            ++aSelStart;
                        }
                    }
                }
                else
                {
                    remove(mSelectionStart, mSelectionEnd-mSelectionStart);
                }
            }
            else
            {
                bool good=true;

                if (mSelectionStart==mSelectionEnd)
                {
                    good=(mSelectionStart<mData.size());
                }

                if (good)
                {
                    int aStartRow=mSelectionStart>>3;
                    mSelectionStart=aStartRow<<3;

                    if ((mSelectionEnd & 7)!=0)
                    {
                        int aEndRow=mSelectionEnd>>3;
                        mSelectionEnd=(aEndRow<<3)+8;
                    }

                    if (mSelectionStart==mSelectionEnd)
                    {
                        mSelectionEnd+=8;
                    }

                    remove(mSelectionStart, mSelectionEnd-mSelectionStart);
                }
            }

            setCursorPosition(aSelStart);
            cursorMoved(false);
        }
        else
        if ((event->key() == Qt::Key_Backspace) && (event->modifiers() == Qt::NoModifier))
        {
            int aSelStart=mSelectionStart;

            if (mCursorAtTheLeft)
            {
                if (mSelectionStart==mSelectionEnd)
                {
                    if (mSelectionStart>0)
                    {
                        if (mMode==INSERT)
                        {
                            remove(mSelectionStart-1, 1);
                        }
                        else
                        {
                            replace(mSelectionStart-1, 0);
                        }

                        --aSelStart;
                    }
                }
                else
                {
                    remove(mSelectionStart, mSelectionEnd-mSelectionStart);
                }
            }
            else
            {
                int aStartRow=mSelectionStart>>3;
                int aEndRow=mSelectionEnd>>3;

                bool good=true;

                if (mSelectionStart==mSelectionEnd)
                {
                    good=(mSelectionStart>0);

                    --aStartRow;
                    --aEndRow;
                    aSelStart=aStartRow<<3;
                    mSelectionEnd=(aEndRow<<3)+8;
                }

                if (good)
                {
                    mSelectionStart=aStartRow<<3;

                    if ((mSelectionEnd & 7)!=0)
                    {
                        mSelectionEnd=(aEndRow<<3)+8;
                    }

                    remove(mSelectionStart, mSelectionEnd-mSelectionStart);
                }
            }

            setCursorPosition(aSelStart);
            cursorMoved(false);
        }
        else
        if (event->matches(QKeySequence::Cut))
        {
            cut();
        }
        else
        if (event->matches(QKeySequence::Paste))
        {
            paste();
        }
        else
        {
            QString aKeyText=event->text();

            if (aKeyText.length()>0)
            {
                char aKey=aKeyText.at(0).toLatin1();

                // TODO: Handle pressing edit buttons

                if (mCursorAtTheLeft)
                {

                }
                else
                {

                }
            }
        }
    }
}

void BitEditor::mousePressEvent(QMouseEvent *event)
{
    mLeftButtonPressed=(event->button()==Qt::LeftButton);

    if (mLeftButtonPressed)
    {
        bool aShift=event->modifiers() & Qt::ShiftModifier;
        int aPosition=charAt(event->pos(), &mCursorAtTheLeft);

        if (aShift)
        {
            if (aPosition>=mSelectionInit)
            {
                ++aPosition;
            }
            else
            {
                mOneMoreSelection=true;
            }
        }

        setCursorPosition(aPosition);
        cursorMoved(aShift);
    }

    QAbstractScrollArea::mousePressEvent(event);
}

void BitEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (mLeftButtonPressed)
    {
        int aPosition=charAt(event->pos(), &mCursorAtTheLeft);

        if (aPosition>=mSelectionInit)
        {
            ++aPosition;
        }
        else
        {
            mOneMoreSelection=true;
        }

        setCursorPosition(aPosition);
        cursorMoved(true);
    }

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

// *********************************************************************************
//                                MultipleBitUndoCommand
// *********************************************************************************

MultipleBitUndoCommand::MultipleBitUndoCommand(BitEditor *aEditor, Type aType, int aPos, int aLength, QBitArray aNewArray, QUndoCommand *parent) :
    QUndoCommand(parent)
{
    mEditor=aEditor;
    mType=aType;
    mPos=aPos;
    mLength=aLength;
    mNewArray=aNewArray;
}

void MultipleBitUndoCommand::insert(int aIndex, const QBitArray &aArray)
{
    if (aArray.size()==0)
    {
        return;
    }

    if (aIndex<0)
    {
        aIndex=0;
    }
    else
    if (aIndex>mEditor->mData.size())
    {
        aIndex=mEditor->mData.size();
    }

    mEditor->mData.resize(mEditor->mData.size()+aArray.size());

    for (int i=mEditor->mData.size()-1; i>=aIndex+aArray.size(); --i)
    {
        mEditor->mData.setBit(i, mEditor->mData.at(i-aArray.size()));
    }

    for (int i=0; i<aArray.size(); ++i)
    {
        mEditor->mData.setBit(aIndex+i, aArray.at(i));
    }
}

void MultipleBitUndoCommand::replace(int aPos, int aLength, const QBitArray &aArray)
{
    remove(aPos, aLength);
    insert(aPos, aArray);
}

void MultipleBitUndoCommand::remove(int aPos, int aLength)
{
    if (aPos<0)
    {
        return;
    }

    if (aLength>mEditor->mData.size()-aPos)
    {
        aLength=mEditor->mData.size()-aPos;
    }

    if (aLength<=0)
    {
        return;
    }

    for (int i=aPos; i<mEditor->mData.size()-aLength; ++i)
    {
        mEditor->mData.setBit(i, mEditor->mData.at(i+aLength));
    }

    mEditor->mData.resize(mEditor->mData.size()-aLength);
}

QBitArray MultipleBitUndoCommand::mid(int aPos, int aLength)
{
    QBitArray aResArray;

    if (aPos<0)
    {
        return aResArray;
    }

    if (aLength<0 || aLength>mEditor->mData.size()-aPos)
    {
        aLength=mEditor->mData.size()-aPos;
    }

    if (aLength<=0)
    {
        return aResArray;
    }

    aResArray.resize(aLength);

    for (int i=0; i<aLength; ++i)
    {
        aResArray.setBit(i, mEditor->mData.at(aPos+i));
    }

    return aResArray;
}

void MultipleBitUndoCommand::undo()
{
    switch (mType)
    {
        case Insert:
        {
            remove(mPos, mNewArray.size());
        }
        break;
        case Replace:
        {
            replace(mPos, mNewArray.size(), mOldArray);
        }
        break;
        case Remove:
        {
            insert(mPos, mOldArray);
        }
        break;
    }

    mEditor->setCursorPosition(mPrevPosition);
}

void MultipleBitUndoCommand::redo()
{
    mPrevPosition=mEditor->mCursorPosition;

    switch (mType)
    {
        case Insert:
        {
            insert(mPos, mNewArray);
        }
        break;
        case Replace:
        {
            mOldArray=mid(mPos, mLength);
            replace(mPos, mLength, mNewArray);
        }
        break;
        case Remove:
        {
            mOldArray=mid(mPos, mLength);
            remove(mPos, mLength);
        }
        break;
    }
}
