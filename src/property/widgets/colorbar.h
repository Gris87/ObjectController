#ifndef COLORBAR_H
#define COLORBAR_H

#include <QWidget>

#include <QPainter>

class ColorBar : public QWidget
{
    Q_OBJECT
public:
    explicit ColorBar(QWidget *parent = 0);

    QColor color();
    void setColor(QColor aColor);

    int value();
    void setValue(int aValue);

    void setValueAt(int y);

protected:
    bool    mLeftPressed;
    QColor  mColor;
    int     mValue;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    void drawFrame(QPainter *p, QRect aRect);

signals:
    void valueChanged(int aValue);
};

#endif // COLORBAR_H
