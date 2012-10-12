#include "bytearrayeditdialog.h"
#include "ui_bytearrayeditdialog.h"

ByteArrayEditDialog::ByteArrayEditDialog(QByteArray aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ByteArrayEditDialog)
{
    ui->setupUi(this);

    mHexEditor=new HexEditor(this);
    mHexEditor->setData(aValue);

    QPalette aPalette=mHexEditor->palette();
    aPalette.setColor(QPalette::AlternateBase, QColor(10, 200, 90));
    mHexEditor->setPalette(aPalette);

    ui->mainLayout->insertWidget(0, mHexEditor);
}

ByteArrayEditDialog::~ByteArrayEditDialog()
{
    delete ui;
}

QByteArray ByteArrayEditDialog::resultValue() const
{
    return mHexEditor->data();
}

void ByteArrayEditDialog::on_okButton_clicked()
{
    accept();
}

void ByteArrayEditDialog::on_cancelButton_clicked()
{
    reject();
}
