#include "bitarrayeditdialog.h"
#include "ui_bitarrayeditdialog.h"

BitArrayEditDialog::BitArrayEditDialog(QBitArray aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BitArrayEditDialog)
{
    ui->setupUi(this);

    mBitEditor=new BitEditor(this);
    mBitEditor->setData(aValue);

    QPalette aPalette=mBitEditor->palette();
    aPalette.setColor(QPalette::AlternateBase, QColor(10, 200, 90));
    mBitEditor->setPalette(aPalette);

    ui->mainLayout->insertWidget(0, mBitEditor);
}

BitArrayEditDialog::~BitArrayEditDialog()
{
    delete ui;
}

QBitArray BitArrayEditDialog::resultValue() const
{
    return mBitEditor->data();
}

void BitArrayEditDialog::on_okButton_clicked()
{
    accept();
}

void BitArrayEditDialog::on_cancelButton_clicked()
{
    reject();
}
