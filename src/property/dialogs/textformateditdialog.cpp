#include "textformateditdialog.h"
#include "ui_textformateditdialog.h"

TextFormatEditDialog::TextFormatEditDialog(QTextFormat aTextFormat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextFormatEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    mTextFormat=aTextFormat;

    // TODO: Implement TextFormat Edit Dialog
}

TextFormatEditDialog::~TextFormatEditDialog()
{
    delete ui;
}

QTextFormat TextFormatEditDialog::resultValue() const
{
    return mTextFormat;
}

void TextFormatEditDialog::on_okButton_clicked()
{
    accept();
}

void TextFormatEditDialog::on_cancelButton_clicked()
{
    reject();
}
