#include "bytearrayeditdialog.h"
#include "ui_bytearrayeditdialog.h"

#include "../propertyutils.h"

ByteArrayEditDialog::ByteArrayEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ByteArrayEditDialog)
{
    init(QByteArray(), 0);
}

ByteArrayEditDialog::ByteArrayEditDialog(QByteArray aValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ByteArrayEditDialog)
{
    init(aValue, 0);
}

ByteArrayEditDialog::ByteArrayEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ByteArrayEditDialog)
{
    init(QByteArray(), aAttributes);
}

ByteArrayEditDialog::ByteArrayEditDialog(QByteArray aValue, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ByteArrayEditDialog)
{
    init(aValue, aAttributes);
}

void ByteArrayEditDialog::init(QByteArray aValue, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    mHexEditor=new HexEditor(this);
    mHexEditor->setData(aValue);

    QPalette aPalette=mHexEditor->palette();
    aPalette.setColor(QPalette::AlternateBase, QColor(10, 200, 90));
    mHexEditor->setPalette(aPalette);

    if (aAttributes)
    {
        aAttributes->applyToWidget(mHexEditor);
    }

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
