#include "transformeditdialog.h"
#include "ui_transformeditdialog.h"

TransformEditDialog::TransformEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransformEditDialog)
{
    init(QTransform(), 0);
}

TransformEditDialog::TransformEditDialog(QTransform aTransform, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransformEditDialog)
{
    init(aTransform, 0);
}

TransformEditDialog::TransformEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransformEditDialog)
{
    init(QTransform(), aAttributes);
}

TransformEditDialog::TransformEditDialog(QTransform aTransform, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransformEditDialog)
{
    init(aTransform, aAttributes);
}

void TransformEditDialog::init(QTransform aTransform, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->m11SpinBox->setValue(aTransform.m11());
    ui->m12SpinBox->setValue(aTransform.m12());
    ui->m13SpinBox->setValue(aTransform.m13());
    ui->m21SpinBox->setValue(aTransform.m21());
    ui->m22SpinBox->setValue(aTransform.m22());
    ui->m23SpinBox->setValue(aTransform.m23());
    ui->m31SpinBox->setValue(aTransform.m31());
    ui->m32SpinBox->setValue(aTransform.m32());
    ui->m33SpinBox->setValue(aTransform.m33());

    if (aAttributes)
    {
        aAttributes->applyToDoubleSpinBox(ui->m11SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m12SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m13SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m21SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m22SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m23SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m31SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m32SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m33SpinBox);
    }
}

TransformEditDialog::~TransformEditDialog()
{
    delete ui;
}

QTransform TransformEditDialog::resultValue()
{
    return QTransform(
                      ui->m11SpinBox->value(), ui->m12SpinBox->value(), ui->m13SpinBox->value(),
                      ui->m21SpinBox->value(), ui->m22SpinBox->value(), ui->m23SpinBox->value(),
                      ui->m31SpinBox->value(), ui->m32SpinBox->value(), ui->m33SpinBox->value()
                     );
}

void TransformEditDialog::on_okButton_clicked()
{
    accept();
}

void TransformEditDialog::on_cancelButton_clicked()
{
    reject();
}
