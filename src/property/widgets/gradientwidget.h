#ifndef GRADIENTWIDGET_H
#define GRADIENTWIDGET_H

#include <QWidget>

#include <QPainter>

class GradientWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GradientWidget(QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    QGradientStops gradientStops() const;
    void setGradientStops(const QGradientStops &aGradientStops);

protected:
    bool           mLeftPressed;
    QGradientStops mGradientStops;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    void drawTransparentArea(QPainter *aPainter, QRect aRect, int aBoxSize=8);
    void drawFrame(QPainter *p, QRect aRect);

signals:
    void gradientChanged(const QGradientStops &aGradientStops);
};

#endif // GRADIENTWIDGET_H
