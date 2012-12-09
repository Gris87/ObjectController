#include "recteditdialog.h"
#include "ui_recteditdialog.h"

RectEditDialog::RectEditDialog(QRect aRect, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RectEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->xSpinBox->setValue(aRect.x());
    ui->ySpinBox->setValue(aRect.y());
    ui->widthSpinBox->setValue(aRect.width());
    ui->heightSpinBox->setValue(aRect.height());
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
