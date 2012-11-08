#include "pointfeditdialog.h"
#include "ui_pointfeditdialog.h"

PointFEditDialog::PointFEditDialog(QPointF aPointF, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointFEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->xSpinBox->setValue(aPointF.x());
    ui->ySpinBox->setValue(aPointF.y());
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
