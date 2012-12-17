#include "quaternioneditdialog.h"
#include "ui_quaternioneditdialog.h"

QuaternionEditDialog::QuaternionEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuaternionEditDialog)
{
    init(QQuaternion(), 0);
}

QuaternionEditDialog::QuaternionEditDialog(QQuaternion aQuaternion, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuaternionEditDialog)
{
    init(aQuaternion, 0);
}

QuaternionEditDialog::QuaternionEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuaternionEditDialog)
{
    init(QQuaternion(), aAttributes);
}

QuaternionEditDialog::QuaternionEditDialog(QQuaternion aQuaternion, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuaternionEditDialog)
{
    init(aQuaternion, aAttributes);
}

void QuaternionEditDialog::init(QQuaternion aQuaternion, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->scalarSpinBox->setValue(aQuaternion.scalar());
    ui->xSpinBox->setValue(aQuaternion.x());
    ui->ySpinBox->setValue(aQuaternion.y());
    ui->zSpinBox->setValue(aQuaternion.z());

    if (aAttributes)
    {
        aAttributes->applyToDoubleSpinBox(ui->scalarSpinBox);
        aAttributes->applyToDoubleSpinBox(ui->xSpinBox);
        aAttributes->applyToDoubleSpinBox(ui->ySpinBox);
        aAttributes->applyToDoubleSpinBox(ui->zSpinBox);
    }
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
