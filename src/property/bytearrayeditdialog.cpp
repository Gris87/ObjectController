#include "bytearrayeditdialog.h"
#include "ui_bytearrayeditdialog.h"

ByteArrayEditDialog::ByteArrayEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ByteArrayEditDialog)
{
    ui->setupUi(this);
}

ByteArrayEditDialog::~ByteArrayEditDialog()
{
    delete ui;
}

QByteArray ByteArrayDialog::resultValue() const
{
    QByteArray res;

    return res;
}
