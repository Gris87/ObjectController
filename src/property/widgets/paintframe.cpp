#include "paintframe.h"
#include "ui_paintframe.h"

PaintFrame::PaintFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintFrame)
{
    ui->setupUi(this);
}

PaintFrame::~PaintFrame()
{
    delete ui;
}

QPixmap PaintFrame::image() const
{
    return QPixmap();
}

void PaintFrame::setImage(const QPixmap &aImage)
{

}
