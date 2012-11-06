#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QUndoCommand>
#include <QColor>

class PaintView : public QGraphicsView
{
    Q_OBJECT

    friend class DrawUndoCommand;

public:
    explicit PaintView(QPixmap aPixmap, QWidget *parent = 0);

    void resizeImage(QSize aNewSize);

    QPixmap image() const;
    void setImage(const QPixmap &aImage);

    QColor firstColor() const;
    void setFirstColor(const QColor &aColor);

    QColor secondColor() const;
    void setSecondColor(const QColor &aColor);

protected:
    QGraphicsPixmapItem *mPixmapItem;
    int                  mStartX;
    int                  mStartY;
    Qt::MouseButton      mMouseButton;
    int                  mLineWidth;
    QColor               mFirstColor;
    QColor               mSecondColor;
    QUndoStack           mUndoStack;

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void drawLine(int x1, int y1, int x2, int y2, const QColor &aColor, bool aNewLine=true);

public slots:
    void undo();
    void redo();
};

// *********************************************************************************

class DrawUndoCommand : public QUndoCommand
{
public:
    DrawUndoCommand(PaintView *aEditor, bool aDrawStart, QPixmap aNewPixmap, QUndoCommand *parent=0);

    void undo();
    void redo();
    bool mergeWith(const QUndoCommand *command);
    int id() const;

private:
    PaintView  *mEditor;
    bool        mDrawStart;
    QPixmap     mNewPixmap;
    QPixmap     mOldPixmap;
};

#endif // PAINTVIEW_H
