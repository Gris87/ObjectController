#include "sizefeditdialog.h"
#include "ui_sizefeditdialog.h"

SizeFEditDialog::SizeFEditDialog(QSizeF aSize, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeFEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->widthSpinBox->setValue(aSize.width());
    ui->heightSpinBox->setValue(aSize.height());
}

SizeFEditDialog::~SizeFEditDialog()
{
    delete ui;
}

QSizeF SizeFEditDialog::resultValue()
{
    return QSizeF(ui->widthSpinBox->value(), ui->heightSpinBox->value());
}

void SizeFEditDialog::on_okButton_clicked()
{
    accept();
}

void SizeFEditDialog::on_cancelButton_clicked()
{
    reject();
}