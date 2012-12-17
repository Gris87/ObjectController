#include "recteditdialog.h"
#include "ui_recteditdialog.h"

RectEditDialog::RectEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RectEditDialog)
{
    init(QRect(), 0);
}

RectEditDialog::RectEditDialog(QRect aRect, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RectEditDialog)
{
    init(aRect, 0);
}

RectEditDialog::RectEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RectEditDialog)
{
    init(QRect(), aAttributes);
}

RectEditDialog::RectEditDialog(QRect aRect, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RectEditDialog)
{
    init(aRect, aAttributes);
}

void RectEditDialog::init(QRect aRect, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->xSpinBox->setValue(aRect.x());
    ui->ySpinBox->setValue(aRect.y());
    ui->widthSpinBox->setValue(aRect.width());
    ui->heightSpinBox->setValue(aRect.height());

    if (aAttributes)
    {
        aAttributes->applyToSpinBox(ui->xSpinBox);
        aAttributes->applyToSpinBox(ui->ySpinBox);
        aAttributes->applyToSpinBox(ui->widthSpinBox);
        aAttributes->applyToSpinBox(ui->heightSpinBox);
    }
}

RectEditDialog::~RectEditDialog()
{
    delete ui;
}

QRect RectEditDialog::resultValue()
{
    return QRect(ui->xSpinBox->value(), ui->ySpinBox->value(), ui->widthSpinBox->value(), ui->heightSpinBox->value());
}

void RectEditDialog::on_okButton_clicked()
{
    accept();
}

void RectEditDialog::on_cancelButton_clicked()
{
    reject();
}
