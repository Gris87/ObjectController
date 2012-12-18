#include "bitarrayeditdialog.h"
#include "ui_bitarrayeditdialog.h"

BitArrayEditDialog::BitArrayEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BitArrayEditDialog)
{
    init(QBitArray(), 0);
}

BitArrayEditDialog::BitArrayEditDialog(QBitArray aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BitArrayEditDialog)
{
    init(aValue, 0);
}

BitArrayEditDialog::BitArrayEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BitArrayEditDialog)
{
    init(QBitArray(), aAttributes);
}

BitArrayEditDialog::BitArrayEditDialog(QBitArray aValue, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BitArrayEditDialog)
{
    init(aValue, aAttributes);
}

void BitArrayEditDialog::init(QBitArray aValue, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    mBitEditor=new BitEditor(this);
    mBitEditor->setData(aValue);

    QPalette aPalette=mBitEditor->palette();
    aPalette.setColor(QPalette::AlternateBase, QColor(10, 200, 90));
    mBitEditor->setPalette(aPalette);

    if (aAttributes)
    {
        aAttributes->applyToWidget(mBitEditor);
    }

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
