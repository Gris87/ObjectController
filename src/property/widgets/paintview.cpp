#include "paintview.h"

#include <QMouseEvent>

PaintView::PaintView(QPixmap aPixmap, QWidget *parent) :
    QGraphicsView(parent)
{
    QGraphicsScene *aScene=new QGraphicsScene(0, 0, aPixmap.width(), aPixmap.height());
    mPixmapItem=aScene->addPixmap(aPixmap);
    setScene(aScene);

    mStartX=0;
    mStartY=0;
    mMouseButton=Qt::NoButton;

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

    QPointF aFirstPoint=mPixmapItem->mapFromScene(aFirstPointF);
    QPointF aSecondPoint=mPixmapItem->mapFromScene(aSecondPointF);

    QPixmap aPixmap=mPixmapItem->pixmap();

    QPainter aPainter(&aPixmap);
    aPainter.setPen(aColor);
    aPainter.drawLine(aFirstPoint, aSecondPoint);
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

QPixmap PaintView::image() const
{
    return mPixmapItem->pixmap();
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
    mOldPixmap=aEditor->mPixmapItem->pixmap();
}

void DrawUndoCommand::undo()
{
    mEditor->mPixmapItem->setPixmap(mOldPixmap);
}

void DrawUndoCommand::redo()
{
    mEditor->mPixmapItem->setPixmap(mNewPixmap);
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
