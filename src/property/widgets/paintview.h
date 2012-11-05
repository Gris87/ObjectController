#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <QGraphicsView>

class PaintView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PaintView(QPixmap aPixmap, QWidget *parent = 0);

    QPixmap image() const;
};

#endif // PAINTVIEW_H
