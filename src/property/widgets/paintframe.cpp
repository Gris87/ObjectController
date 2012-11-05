#include "paintframe.h"
#include "ui_paintframe.h"

PaintFrame::PaintFrame(QPixmap aValue, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintFrame)
{
    ui->setupUi(this);

    mImageView=new PaintView(aValue, this);

    ui->mainLayout->insertWidget(0, mImageView);
}

PaintFrame::~PaintFrame()
{
    delete ui;
}

QPixmap PaintFrame::image() const
{
    return mImageView->image();
}
