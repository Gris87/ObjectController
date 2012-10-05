#include "bytearrayeditdialog.h"
#include "ui_bytearrayeditdialog.h"

ByteArrayEditDialog::ByteArrayEditDialog(QByteArray aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ByteArrayEditDialog)
{
    ui->setupUi(this);
}

ByteArrayEditDialog::~ByteArrayEditDialog()
{
    delete ui;
}

QByteArray ByteArrayEditDialog::resultValue() const
{
    QByteArray res;

    return res;
}
