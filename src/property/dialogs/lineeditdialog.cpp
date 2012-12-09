#include "lineeditdialog.h"
#include "ui_lineeditdialog.h"

LineEditDialog::LineEditDialog(QLine aLine, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->x1SpinBox->setValue(aLine.x1());
    ui->y1SpinBox->setValue(aLine.y1());
    ui->x2SpinBox->setValue(aLine.x2());
    ui->y2SpinBox->setValue(aLine.y2());
}

LineEditDialog::~LineEditDialog()
{
    delete ui;
}

QLine LineEditDialog::resultValue()
{
    return QLine(ui->x1SpinBox->value(), ui->y1SpinBox->value(), ui->x2SpinBox->value(), ui->y2SpinBox->value());
}

void LineEditDialog::on_okButton_clicked()
{
    accept();
}

void LineEditDialog::on_cancelButton_clicked()
{
    reject();
}
