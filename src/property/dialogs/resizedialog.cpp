#include "resizedialog.h"
#include "ui_resizedialog.h"

ResizeDialog::ResizeDialog(QSize aSize, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResizeDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->widthSpinBox->setValue(aSize.width());
    ui->heightSpinBox->setValue(aSize.height());
}

ResizeDialog::~ResizeDialog()
{
    delete ui;
}

QSize ResizeDialog::newSize()
{
    return QSize(ui->widthSpinBox->value(), ui->heightSpinBox->value());
}

void ResizeDialog::on_okButton_clicked()
{
    accept();
}

void ResizeDialog::on_cancelButton_clicked()
{
    reject();
}
