#include "sizefeditdialog.h"
#include "ui_sizefeditdialog.h"

SizeFEditDialog::SizeFEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeFEditDialog)
{
    init(QSizeF(), 0);
}

SizeFEditDialog::SizeFEditDialog(QSizeF aSize, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeFEditDialog)
{
    init(aSize, 0);
}

SizeFEditDialog::SizeFEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeFEditDialog)
{
    init(QSizeF(), aAttributes);
}

SizeFEditDialog::SizeFEditDialog(QSizeF aSize, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeFEditDialog)
{
    init(aSize, aAttributes);
}

void SizeFEditDialog::init(QSizeF aSize, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->widthSpinBox->setValue(aSize.width());
    ui->heightSpinBox->setValue(aSize.height());

    if (aAttributes)
    {
        aAttributes->applyToDoubleSpinBox(ui->widthSpinBox);
        aAttributes->applyToDoubleSpinBox(ui->heightSpinBox);
    }
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
