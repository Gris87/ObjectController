#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QColor>

class PaintView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PaintView(QPixmap aPixmap, QWidget *parent = 0);

    QPixmap image() const;

    QColor firstColor() const;
    void setFirstColor(const QColor &aColor);

    QColor secondColor() const;
    void setSecondColor(const QColor &aColor);

protected:
    QGraphicsPixmapItem *mPixmapItem;
    QColor               mFirstColor;
    QColor               mSecondColor;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // PAINTVIEW_H
