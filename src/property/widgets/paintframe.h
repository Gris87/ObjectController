#ifndef PAINTFRAME_H
#define PAINTFRAME_H

#include <QWidget>

#include "../widgets/paintview.h"

namespace Ui {
class PaintFrame;
}

class PaintFrame : public QWidget
{
    Q_OBJECT

public:
    explicit PaintFrame(QPixmap aValue, QWidget *parent = 0);
    ~PaintFrame();

    QPixmap image() const;

private:
    Ui::PaintFrame *ui;
    PaintView      *mImageView;
};

#endif // PAINTFRAME_H
