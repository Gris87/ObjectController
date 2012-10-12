#include "bytearrayeditdialog.h"
#include "ui_bytearrayeditdialog.h"

#include "../widgets/hexeditor.h"

ByteArrayEditDialog::ByteArrayEditDialog(QByteArray aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ByteArrayEditDialog)
{
    ui->setupUi(this);

    ui->hexWidget->setData(aValue);
}

ByteArrayEditDialog::~ByteArrayEditDialog()
{
    delete ui;
}

QByteArray ByteArrayEditDialog::resultValue() const
{
    return ui->hexWidget->data();
}

void ByteArrayEditDialog::on_okButton_clicked()
{
    accept();
}

void ByteArrayEditDialog::on_cancelButton_clicked()
{
    reject();
}
