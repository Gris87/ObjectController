#include "bitarrayeditdialog.h"
#include "ui_bitarrayeditdialog.h"

BitArrayEditDialog::BitArrayEditDialog(QBitArray aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BitArrayEditDialog)
{
    ui->setupUi(this);
}

BitArrayEditDialog::~BitArrayEditDialog()
{
    delete ui;
}

QBitArray BitArrayEditDialog::resultValue() const
{
    QBitArray res;

    return res;
}
