#include "pointeditdialog.h"
#include "ui_pointeditdialog.h"

PointEditDialog::PointEditDialog(QPoint aPoint, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->xSpinBox->setValue(aPoint.x());
    ui->ySpinBox->setValue(aPoint.y());
}

PointEditDialog::~PointEditDialog()
{
    delete ui;
}

QPoint PointEditDialog::resultValue()
{
    return QPoint(ui->xSpinBox->value(), ui->ySpinBox->value());
}

void PointEditDialog::on_okButton_clicked()
{
    accept();
}

void PointEditDialog::on_cancelButton_clicked()
{
    reject();
}
