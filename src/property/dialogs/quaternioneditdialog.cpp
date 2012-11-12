#include "quaternioneditdialog.h"
#include "ui_quaternioneditdialog.h"

QuaternionEditDialog::QuaternionEditDialog(QQuaternion aQuaternion, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuaternionEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->scalarSpinBox->setValue(aQuaternion.scalar());
    ui->xSpinBox->setValue(aQuaternion.x());
    ui->ySpinBox->setValue(aQuaternion.y());
    ui->zSpinBox->setValue(aQuaternion.z());
}

QuaternionEditDialog::~QuaternionEditDialog()
{
    delete ui;
}

QQuaternion QuaternionEditDialog::resultValue()
{
    return QQuaternion(ui->scalarSpinBox->value(), ui->xSpinBox->value(), ui->ySpinBox->value(), ui->zSpinBox->value());
}

void QuaternionEditDialog::on_okButton_clicked()
{
    accept();
}

void QuaternionEditDialog::on_cancelButton_clicked()
{
    reject();
}
