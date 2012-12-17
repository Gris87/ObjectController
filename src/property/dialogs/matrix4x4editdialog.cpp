#include "matrix4x4editdialog.h"
#include "ui_matrix4x4editdialog.h"

Matrix4x4EditDialog::Matrix4x4EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Matrix4x4EditDialog)
{
    init(QMatrix4x4(), 0);
}

Matrix4x4EditDialog::Matrix4x4EditDialog(QMatrix4x4 aMatrix4x4, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Matrix4x4EditDialog)
{
    init(aMatrix4x4, 0);
}

Matrix4x4EditDialog::Matrix4x4EditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Matrix4x4EditDialog)
{
    init(QMatrix4x4(), aAttributes);
}

Matrix4x4EditDialog::Matrix4x4EditDialog(QMatrix4x4 aMatrix4x4, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Matrix4x4EditDialog)
{
    init(aMatrix4x4, aAttributes);
}

void Matrix4x4EditDialog::init(QMatrix4x4 aMatrix4x4, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    qreal aMatrix[16];
    aMatrix4x4.copyDataTo(aMatrix);

    ui->m11SpinBox->setValue(aMatrix[0]);
    ui->m12SpinBox->setValue(aMatrix[1]);
    ui->m13SpinBox->setValue(aMatrix[2]);
    ui->m14SpinBox->setValue(aMatrix[3]);
    ui->m21SpinBox->setValue(aMatrix[4]);
    ui->m22SpinBox->setValue(aMatrix[5]);
    ui->m23SpinBox->setValue(aMatrix[6]);
    ui->m24SpinBox->setValue(aMatrix[7]);
    ui->m31SpinBox->setValue(aMatrix[8]);
    ui->m32SpinBox->setValue(aMatrix[9]);
    ui->m33SpinBox->setValue(aMatrix[10]);
    ui->m34SpinBox->setValue(aMatrix[11]);
    ui->m41SpinBox->setValue(aMatrix[12]);
    ui->m42SpinBox->setValue(aMatrix[13]);
    ui->m43SpinBox->setValue(aMatrix[14]);
    ui->m44SpinBox->setValue(aMatrix[15]);

    if (aAttributes)
    {
        aAttributes->applyToDoubleSpinBox(ui->m11SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m12SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m13SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m14SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m21SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m22SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m23SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m24SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m31SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m32SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m33SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m34SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m41SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m42SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m43SpinBox);
        aAttributes->applyToDoubleSpinBox(ui->m44SpinBox);
    }
}

Matrix4x4EditDialog::~Matrix4x4EditDialog()
{
    delete ui;
}

QMatrix4x4 Matrix4x4EditDialog::resultValue()
{
    return QMatrix4x4(
                      ui->m11SpinBox->value(), ui->m12SpinBox->value(), ui->m13SpinBox->value(), ui->m14SpinBox->value(),
                      ui->m21SpinBox->value(), ui->m22SpinBox->value(), ui->m23SpinBox->value(), ui->m24SpinBox->value(),
                      ui->m31SpinBox->value(), ui->m32SpinBox->value(), ui->m33SpinBox->value(), ui->m34SpinBox->value(),
                      ui->m41SpinBox->value(), ui->m42SpinBox->value(), ui->m43SpinBox->value(), ui->m44SpinBox->value()
                     );
}

void Matrix4x4EditDialog::on_okButton_clicked()
{
    accept();
}

void Matrix4x4EditDialog::on_cancelButton_clicked()
{
    reject();
}
