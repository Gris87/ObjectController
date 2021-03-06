#include "vector4deditdialog.h"
#include "ui_vector4deditdialog.h"

Vector4DEditDialog::Vector4DEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vector4DEditDialog)
{
    init(QVector4D(), 0);
}

Vector4DEditDialog::Vector4DEditDialog(QVector4D aVector4D, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vector4DEditDialog)
{
    init(aVector4D, 0);
}

Vector4DEditDialog::Vector4DEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vector4DEditDialog)
{
    init(QVector4D(), aAttributes);
}

Vector4DEditDialog::Vector4DEditDialog(QVector4D aVector4D, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vector4DEditDialog)
{
    init(aVector4D, aAttributes);
}

void Vector4DEditDialog::init(QVector4D aVector4D, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->xSpinBox->setValue(aVector4D.x());
    ui->ySpinBox->setValue(aVector4D.y());
    ui->zSpinBox->setValue(aVector4D.z());
    ui->wSpinBox->setValue(aVector4D.w());

    if (aAttributes)
    {
        aAttributes->applyToDoubleSpinBox(ui->xSpinBox);
        aAttributes->applyToDoubleSpinBox(ui->ySpinBox);
        aAttributes->applyToDoubleSpinBox(ui->zSpinBox);
        aAttributes->applyToDoubleSpinBox(ui->wSpinBox);
    }
}

Vector4DEditDialog::~Vector4DEditDialog()
{
    delete ui;
}

QVector4D Vector4DEditDialog::resultValue()
{
    return QVector4D(ui->xSpinBox->value(), ui->ySpinBox->value(), ui->zSpinBox->value(), ui->wSpinBox->value());
}

void Vector4DEditDialog::on_okButton_clicked()
{
    accept();
}

void Vector4DEditDialog::on_cancelButton_clicked()
{
    reject();
}
