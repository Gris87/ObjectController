#include "pointfeditdialog.h"
#include "ui_pointfeditdialog.h"

PointFEditDialog::PointFEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointFEditDialog)
{
    init(QPointF(), 0);
}

PointFEditDialog::PointFEditDialog(QPointF aPointF, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointFEditDialog)
{
    init(aPointF, 0);
}

PointFEditDialog::PointFEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointFEditDialog)
{
    init(QPointF(), aAttributes);
}

PointFEditDialog::PointFEditDialog(QPointF aPointF, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointFEditDialog)
{
    init(aPointF, aAttributes);
}

void PointFEditDialog::init(QPointF aPointF, const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->xSpinBox->setValue(aPointF.x());
    ui->ySpinBox->setValue(aPointF.y());

    if (aAttributes)
    {
        aAttributes->applyToDoubleSpinBox(ui->xSpinBox);
        aAttributes->applyToDoubleSpinBox(ui->ySpinBox);
    }
}

PointFEditDialog::~PointFEditDialog()
{
    delete ui;
}

QPointF PointFEditDialog::resultValue()
{
    return QPointF(ui->xSpinBox->value(), ui->ySpinBox->value());
}

void PointFEditDialog::on_okButton_clicked()
{
    accept();
}

void PointFEditDialog::on_cancelButton_clicked()
{
    reject();
}
