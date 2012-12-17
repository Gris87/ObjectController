#include "sizeeditdialog.h"
#include "ui_sizeeditdialog.h"

SizeEditDialog::SizeEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeEditDialog)
{
    init(QSize(), 0);
}

SizeEditDialog::SizeEditDialog(QSize aSize, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeEditDialog)
{
    init(aSize, 0);
}

SizeEditDialog::SizeEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeEditDialog)
{
    init(QSize(), aAttributes);
}

SizeEditDialog::SizeEditDialog(QSize aSize, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeEditDialog)
{
    init(aSize, aAttributes);
}

void SizeEditDialog::init(QSize aSize, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->widthSpinBox->setValue(aSize.width());
    ui->heightSpinBox->setValue(aSize.height());

    if (aAttributes)
    {
        aAttributes->applyToSpinBox(ui->widthSpinBox);
        aAttributes->applyToSpinBox(ui->heightSpinBox);
    }
}

SizeEditDialog::~SizeEditDialog()
{
    delete ui;
}

QSize SizeEditDialog::resultValue()
{
    return QSize(ui->widthSpinBox->value(), ui->heightSpinBox->value());
}

void SizeEditDialog::on_okButton_clicked()
{
    accept();
}

void SizeEditDialog::on_cancelButton_clicked()
{
    reject();
}
