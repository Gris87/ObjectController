#include "pointeditdialog.h"
#include "ui_pointeditdialog.h"

PointEditDialog::PointEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointEditDialog)
{
    init(QPoint(), 0);
}

PointEditDialog::PointEditDialog(QPoint aPoint, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointEditDialog)
{
    init(aPoint, 0);
}

PointEditDialog::PointEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointEditDialog)
{
    init(QPoint(), aAttributes);
}

PointEditDialog::PointEditDialog(QPoint aPoint, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointEditDialog)
{
    init(aPoint, aAttributes);
}

void PointEditDialog::init(QPoint aPoint, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->xSpinBox->setValue(aPoint.x());
    ui->ySpinBox->setValue(aPoint.y());

    if (aAttributes)
    {
        aAttributes->applyToSpinBox(ui->xSpinBox);
        aAttributes->applyToSpinBox(ui->ySpinBox);
    }
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
