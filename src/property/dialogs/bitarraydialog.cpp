#include "bitarraydialog.h"
#include "ui_bitarraydialog.h"

BitArrayDialog::BitArrayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BitArrayDialog)
{
    ui->setupUi(this);
}

BitArrayDialog::~BitArrayDialog()
{
    delete ui;
}

QBitArray BitArrayDialog::resultValue() const
{
    QBitArray res;

    return res;
}
