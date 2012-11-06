#include "paintdialog.h"
#include "ui_paintdialog.h"

PaintDialog::PaintDialog(QPixmap aValue, bool aMono, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    mPaintFrame=new PaintFrame(aValue, aMono, this);
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
