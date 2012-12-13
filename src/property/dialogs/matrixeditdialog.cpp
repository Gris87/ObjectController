#include "matrixeditdialog.h"
#include "ui_matrixeditdialog.h"

MatrixEditDialog::MatrixEditDialog(QMatrix aMatrix, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MatrixEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->m11SpinBox->setValue(aMatrix.m11());
    ui->m12SpinBox->setValue(aMatrix.m12());
    ui->m21SpinBox->setValue(aMatrix.m21());
    ui->m22SpinBox->setValue(aMatrix.m22());
    ui->dxSpinBox->setValue(aMatrix.dx());
    ui->dySpinBox->setValue(aMatrix.dy());

    if (aAttributes)
    {
        aAttributes->applyToDoubleSpinBox(ui->m11SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m12SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m21SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m22SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->dxSpinBox);
        aAttributes->applyToDoubleSpinBox(ui->dySpinBox);
    }
}

MatrixEditDialog::~MatrixEditDialog()
{
    delete ui;
}

QMatrix MatrixEditDialog::resultValue()
{
    return QMatrix(
                   ui->m11SpinBox->value(), ui->m12SpinBox->value(),
                   ui->m21SpinBox->value(), ui->m22SpinBox->value(),
                   ui->dxSpinBox->value(), ui->dySpinBox->value()
                  );
}

void MatrixEditDialog::on_okButton_clicked()
{
    accept();
}

void MatrixEditDialog::on_cancelButton_clicked()
{
    reject();
}
