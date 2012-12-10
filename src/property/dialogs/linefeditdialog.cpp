#include "linefeditdialog.h"
#include "ui_linefeditdialog.h"

LineFEditDialog::LineFEditDialog(QLineF aLineF, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineFEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->x1SpinBox->setValue(aLineF.x1());
    ui->y1SpinBox->setValue(aLineF.y1());
    ui->x2SpinBox->setValue(aLineF.x2());
    ui->y2SpinBox->setValue(aLineF.y2());

    if (aAttributes)
    {
        aAttributes->applyToDoubleSpinBox(ui->x1SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->y1SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->x2SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->y2SpinBox);
    }
}

LineFEditDialog::~LineFEditDialog()
{
    delete ui;
}

QLineF LineFEditDialog::resultValue()
{
    return QLineF(ui->x1SpinBox->value(), ui->y1SpinBox->value(), ui->x2SpinBox->value(), ui->y2SpinBox->value());
}

void LineFEditDialog::on_okButton_clicked()
{
    accept();
}

void LineFEditDialog::on_cancelButton_clicked()
{
    reject();
}
