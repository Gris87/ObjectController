#ifndef PAINTFRAME_H
#define PAINTFRAME_H

#include <QWidget>

#include "colorarea.h"
#include "paintview.h"

namespace Ui {
class PaintFrame;
}

class PaintFrame : public QWidget
{
    Q_OBJECT

public:
    explicit PaintFrame(QPixmap aValue, bool aMono, QWidget *parent = 0);
    ~PaintFrame();

    QPixmap image() const;

private:
    Ui::PaintFrame *ui;
    PaintView      *mImageView;
    ColorArea      *mLeftArea;
    ColorArea      *mRightArea;

private slots:
    void colorLeftSelected(ColorArea *aArea);
    void colorRightSelected(ColorArea *aArea);
    void leftColorChanged(QColor aColor);
    void rightColorChanged(QColor aColor);
};

#endif // PAINTFRAME_H
