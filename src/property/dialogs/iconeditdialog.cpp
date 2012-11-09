#include "iconeditdialog.h"
#include "ui_iconeditdialog.h"

IconEditDialog::IconEditDialog(QIcon aIcon, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IconEditDialog)
{
    ui->setupUi(this);
}

IconEditDialog::~IconEditDialog()
{
    delete ui;
}

QIcon IconEditDialog::resultValue() const
{
    QIcon aIcon;

    return aIcon;
}

void IconEditDialog::on_okButton_clicked()
{
    accept();
}

void IconEditDialog::on_cancelButton_clicked()
{
    reject();
}
