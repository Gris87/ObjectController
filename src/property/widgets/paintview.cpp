#include "paintview.h"

#include <QMouseEvent>
#include <QScrollBar>

PaintView::PaintView(QPixmap aPixmap, QWidget *parent) :
    QGraphicsView(parent)
{
    QGraphicsScene *aScene=new QGraphicsScene(0, 0, aPixmap.width(), aPixmap.height());
    mPixmapItem=aScene->addPixmap(QPixmap());
    putImage(aPixmap);
    setScene(aScene);

    mStartX=0;
    mStartY=0;
    mMouseButton=Qt::NoButton;

    mLineWidth=1;
    mFirstColor.setRgb(0, 0, 0);
    mSecondColor.setRgb(255, 255, 255);
}

void PaintView::keyPressEvent(QKeyEvent *event)
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
    if (
        event->key()==Qt::Key_Plus
        &&
        (
         event->modifiers()==Qt::NoModifier
         ||
         event->modifiers()==Qt::KeypadModifier
        )
       )
    {
        increaseLineWidth();
    }
    else
    if (
        event->key()==Qt::Key_Minus
        &&
        (
         event->modifiers()==Qt::NoModifier
         ||
         event->modifiers()==Qt::KeypadModifier
        )
       )
    {
        decreaseLineWidth();
    }
    else
    {
        QGraphicsView::keyPressEvent(event);
    }
}

void PaintView::mousePressEvent(QMouseEvent *event)
{
    mStartX=event->x();
    mStartY=event->y();

    mMouseButton=event->button();

    if (mMouseButton==Qt::LeftButton)
    {
        drawLine(mStartX, mStartY, mStartX, mStartY, mFirstColor, true);
    }
    else
    if (mMouseButton==Qt::RightButton)
    {
        drawLine(mStartX, mStartY, mStartX, mStartY, mSecondColor, true);
    }
}

void PaintView::mouseMoveEvent(QMouseEvent *event)
{
    if (mMouseButton==Qt::LeftButton)
    {
        drawLine(mStartX, mStartY, event->x(), event->y(), mFirstColor, false);
    }
    else
    if (mMouseButton==Qt::RightButton)
    {
        drawLine(mStartX, mStartY, event->x(), event->y(), mSecondColor, false);
    }

    mStartX=event->x();
    mStartY=event->y();
}

void PaintView::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    mMouseButton=Qt::NoButton;
}

void PaintView::wheelEvent(QWheelEvent *event)
{
    if (event->delta()<0)
    {
        scale(1.1, 1.1);
    }
    else
    {
        scale(0.9, 0.9);
    }
}

void PaintView::drawLine(int x1, int y1, int x2, int y2, const QColor &aColor, bool aNewLine)
{
    QPointF aFirstPointF=mapToScene(x1, y1);
    QPointF aSecondPointF=mapToScene(x2, y2);

    QPoint aFirstPoint=mPixmapItem->mapFromScene(aFirstPointF).toPoint()-QPoint(1, 1);
    QPoint aSecondPoint=mPixmapItem->mapFromScene(aSecondPointF).toPoint()-QPoint(1, 1);



    QPixmap aPixmap=image();

    QPainter aPainter(&aPixmap);

    if (aFirstPoint==aSecondPoint)
    {
        aPainter.setPen(aColor);
        aPainter.setBrush(QBrush(aColor));

        if (mLineWidth>1)
        {
            aPainter.drawEllipse(aFirstPoint, mLineWidth >> 1, mLineWidth >> 1);
        }
        else
        {
            aPainter.drawPoint(aFirstPoint);
        }
    }
    else
    {
        aPainter.setPen(QPen(QBrush(aColor), mLineWidth, Qt::SolidLine, Qt::RoundCap));
        aPainter.drawLine(aFirstPoint, aSecondPoint);
    }


    aPainter.end();

    DrawUndoCommand *aCommand=new DrawUndoCommand(this, aNewLine, aPixmap);
    mUndoStack.push(aCommand);
}

void PaintView::undo()
{
    mUndoStack.undo();
}

void PaintView::redo()
{
    mUndoStack.redo();
}

void PaintView::increaseLineWidth()
{
    if (mLineWidth<1000)
    {
        ++mLineWidth;
    }
}

void PaintView::decreaseLineWidth()
{
    if (mLineWidth>1)
    {
        --mLineWidth;
    }
}

void PaintView::resizeImage(QSize aNewSize)
{
    QPixmap aPixmap=image().scaled(aNewSize);

    DrawUndoCommand *aCommand=new DrawUndoCommand(this, true, aPixmap);
    mUndoStack.push(aCommand);
}

QPixmap PaintView::image() const
{
    QPixmap aPixmap=mPixmapItem->pixmap();
    return aPixmap.copy(1, 1, aPixmap.width()-2, aPixmap.height()-2);
}

void PaintView::setImage(const QPixmap &aImage)
{
    bool aSizeChanged=(image().size()!=aImage.size());

    putImage(aImage);
    mUndoStack.clear();

    if (aSizeChanged)
    {
        setSceneRect(0, 0, aImage.width()+2, aImage.height()+2);
    }

    resetTransform();
    horizontalScrollBar()->setValue(0);
    verticalScrollBar()->setValue(0);

    mLineWidth=1;
}

void PaintView::putImage(const QPixmap &aImage)
{
    QPixmap aNewPixmap(aImage.width()+2, aImage.height()+2);
    aNewPixmap.fill(QColor(255, 255, 255));

    QPainter aPainter(&aNewPixmap);
    aPainter.setPen(QPen(QBrush(QColor(128, 128, 128)), 1, Qt::DotLine));
    aPainter.setBrush(Qt::NoBrush);
    aPainter.drawRect(0, 0, aNewPixmap.width()-1, aNewPixmap.height()-1);
    aPainter.drawPixmap(1, 1, aImage);
    aPainter.end();

    mPixmapItem->setPixmap(aNewPixmap);
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

// *********************************************************************************
//                                 DrawUndoCommand
// *********************************************************************************

DrawUndoCommand::DrawUndoCommand(PaintView *aEditor, bool aDrawStart, QPixmap aNewPixmap, QUndoCommand *parent) :
    QUndoCommand(parent)
{
    mEditor=aEditor;
    mDrawStart=aDrawStart;
    mNewPixmap=aNewPixmap;
    mOldPixmap=aEditor->image();
}

void DrawUndoCommand::undo()
{
    mEditor->putImage(mOldPixmap);

    if (mOldPixmap.size()!=mNewPixmap.size())
    {
        mEditor->setSceneRect(0, 0, mOldPixmap.width()+2, mOldPixmap.height()+2);
    }
}

void DrawUndoCommand::redo()
{
    mEditor->putImage(mNewPixmap);

    if (mOldPixmap.size()!=mNewPixmap.size())
    {
        mEditor->setSceneRect(0, 0, mNewPixmap.width()+2, mNewPixmap.height()+2);
    }
}

bool DrawUndoCommand::mergeWith(const QUndoCommand *command)
{
    DrawUndoCommand *aAnotherCommand=(DrawUndoCommand *)command;

    if (
        mDrawStart
        &&
        !aAnotherCommand->mDrawStart
       )
    {
        mNewPixmap=aAnotherCommand->mNewPixmap;
        return true;
    }

    return false;
}

int DrawUndoCommand::id() const
{
    return 1;
}
