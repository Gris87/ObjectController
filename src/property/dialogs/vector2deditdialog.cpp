#include "vector2deditdialog.h"
#include "ui_vector2deditdialog.h"

Vector2DEditDialog::Vector2DEditDialog(QVector2D aVector2D, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vector2DEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->xSpinBox->setValue(aVector2D.x());
    ui->ySpinBox->setValue(aVector2D.y());

    if (aAttributes)
    {
        aAttributes->applyToDoubleSpinBox(ui->xSpinBox);
        aAttributes->applyToDoubleSpinBox(ui->ySpinBox);
    }
}

Vector2DEditDialog::~Vector2DEditDialog()
{
    delete ui;
}

QVector2D Vector2DEditDialog::resultValue()
{
    return QVector2D(ui->xSpinBox->value(), ui->ySpinBox->value());
}

void Vector2DEditDialog::on_okButton_clicked()
{
    accept();
}

void Vector2DEditDialog::on_cancelButton_clicked()
{
    reject();
}
