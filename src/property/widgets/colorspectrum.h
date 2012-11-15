#ifndef COLORSPECTRUM_H
#define COLORSPECTRUM_H

#include <QFrame>

class ColorSpectrum : public QFrame
{
    Q_OBJECT
public:
    explicit ColorSpectrum(QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    QColor color() const;
    void setColor(const QColor &aColor);

    void setColorAt(int x, int y);

protected:
    bool    mLeftPressed;
    QColor  mColor;
    QPixmap mSpectrumPixmap;

    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    void updateSpectrum();

signals:
    void colorChanged(QColor aColor);
};

#endif // COLORSPECTRUM_H
