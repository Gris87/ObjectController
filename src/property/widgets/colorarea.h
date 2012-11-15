#ifndef COLORAREA_H
#define COLORAREA_H

#include <QFrame>

class ColorArea : public QFrame
{
    Q_OBJECT
public:
    explicit ColorArea(QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &aColor);

    int transparentBlockSize() const;
    void setTransparentBlockSize(const int &aTransparentBlockSize);

    bool isNeedDrawFrame() const;
    void setNeedDrawFrame(const bool &aNeedDrawFrame);

    bool isSelected() const;
    void setSelected(const bool &aSelected);

    bool isSelectAllowed() const;
    void setSelectAllowed(const bool &aSelectAllowed);

    bool isPopupAllowed() const;
    void setPopupAllowed(const bool &aPopupAllowed);

    quint8 popupCount() const;
    void setPopupCount(const quint8 &aPopupCount);

    quint8 popupCellSize() const;
    void setPopupCellSize(const quint8 &aPopupCellSize);

protected:
    QWidget *mPopupWidget;
    QColor   mColor;
    int      mTransparentBlockSize;
    bool     mNeedDrawFrame;
    bool     mSelected;
    bool     mSelectAllowed;
    bool     mPopupAllowed;
    quint8   mPopupCount;
    quint8   mPopupCellSize;

    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void drawTransparentArea(QPainter *aPainter, QRect aRect, int aBoxSize=8);

private slots:
    void cellClicked();

signals:
    void clicked();
    void rightClicked();
    void colorChanged(const QColor &aColor);
};

#endif // COLORAREA_H
