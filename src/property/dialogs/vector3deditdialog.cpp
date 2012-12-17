#include "vector3deditdialog.h"
#include "ui_vector3deditdialog.h"

Vector3DEditDialog::Vector3DEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vector3DEditDialog)
{
    init(QVector3D(), 0);
}

Vector3DEditDialog::Vector3DEditDialog(QVector3D aVector3D, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vector3DEditDialog)
{
    init(aVector3D, 0);
}

Vector3DEditDialog::Vector3DEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vector3DEditDialog)
{
    init(QVector3D(), aAttributes);
}

Vector3DEditDialog::Vector3DEditDialog(QVector3D aVector3D, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vector3DEditDialog)
{
    init(aVector3D, aAttributes);
}

void Vector3DEditDialog::init(QVector3D aVector3D, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->xSpinBox->setValue(aVector3D.x());
    ui->ySpinBox->setValue(aVector3D.y());
    ui->zSpinBox->setValue(aVector3D.z());

    if (aAttributes)
    {
        aAttributes->applyToDoubleSpinBox(ui->xSpinBox);
        aAttributes->applyToDoubleSpinBox(ui->ySpinBox);
        aAttributes->applyToDoubleSpinBox(ui->zSpinBox);
    }
}

Vector3DEditDialog::~Vector3DEditDialog()
{
    delete ui;
}

QVector3D Vector3DEditDialog::resultValue()
{
    return QVector3D(ui->xSpinBox->value(), ui->ySpinBox->value(), ui->zSpinBox->value());
}

void Vector3DEditDialog::on_okButton_clicked()
{
    accept();
}

void Vector3DEditDialog::on_cancelButton_clicked()
{
    reject();
}
