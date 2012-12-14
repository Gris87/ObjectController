#ifndef GRADIENTWIDGET_H
#define GRADIENTWIDGET_H

#include <QWidget>

#include <QPainter>

#include "../propertyattributes.h"

class GradientWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GradientWidget(const PropertyAttributes *aAttributes, QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    QGradientStops gradientStops() const;
    void setGradientStops(const QGradientStops &aGradientStops);

protected:
    bool           mLeftPressed;
    int            mStartX;
    int            mStartY;
    int            mSelectedIndex;
    bool           mDragging;
    QGradientStops mGradientStops;
    const PropertyAttributes *mAttributes;

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
