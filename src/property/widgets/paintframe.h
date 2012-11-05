#ifndef PAINTFRAME_H
#define PAINTFRAME_H

#include <QWidget>

namespace Ui {
class PaintFrame;
}

class PaintFrame : public QWidget
{
    Q_OBJECT

public:
    explicit PaintFrame(QWidget *parent = 0);
    ~PaintFrame();

    QPixmap image() const;
    void setImage(const QPixmap &aImage);

private:
    Ui::PaintFrame *ui;
};

#endif // PAINTFRAME_H
