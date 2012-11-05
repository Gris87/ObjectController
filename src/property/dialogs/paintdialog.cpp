#include "paintdialog.h"
#include "ui_paintdialog.h"

PaintDialog::PaintDialog(QPixmap aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintDialog)
{
    ui->setupUi(this);

    mPaintFrame=new PaintFrame(aValue, this);

    ui->mainLayout->insertWidget(0, mPaintFrame);
}

PaintDialog::~PaintDialog()
{
    delete ui;
}

QPixmap PaintDialog::resultValue() const
{
    return mPaintFrame->image();
}

void PaintDialog::on_okButton_clicked()
{
    accept();
}

void PaintDialog::on_cancelButton_clicked()
{
    reject();
}
