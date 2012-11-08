#include "rectfeditdialog.h"
#include "ui_rectfeditdialog.h"

RectFEditDialog::RectFEditDialog(QRectF aRectF, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RectFEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->xSpinBox->setValue(aRectF.x());
    ui->ySpinBox->setValue(aRectF.y());
    ui->widthSpinBox->setValue(aRectF.width());
    ui->heightSpinBox->setValue(aRectF.height());
}

RectFEditDialog::~RectFEditDialog()
{
    delete ui;
}

QRectF RectFEditDialog::resultValue()
{
    return QRectF(ui->xSpinBox->value(), ui->ySpinBox->value(), ui->widthSpinBox->value(), ui->heightSpinBox->value());
}

void RectFEditDialog::on_okButton_clicked()
{
    accept();
}

void RectFEditDialog::on_cancelButton_clicked()
{
    reject();
}