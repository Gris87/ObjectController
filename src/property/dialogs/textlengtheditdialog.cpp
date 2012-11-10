#include "textlengtheditdialog.h"
#include "ui_textlengtheditdialog.h"

TextLengthEditDialog::TextLengthEditDialog(QTextLength aTextLength, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextLengthEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    QString aTypeStr;

    switch (aTextLength.type())
    {
        case QTextLength::VariableLength:
            aTypeStr="VariableLength";
        break;
        case QTextLength::FixedLength:
            aTypeStr="FixedLength";
        break;
        case QTextLength::PercentageLength:
            aTypeStr="PercentageLength";
        break;
    }

    ui->typeComboBox->setCurrentIndex(ui->typeComboBox->findText(aTypeStr));
    ui->valueSpinBox->setValue(aTextLength.rawValue());
}

TextLengthEditDialog::~TextLengthEditDialog()
{
    delete ui;
}

QTextLength TextLengthEditDialog::resultValue()
{
    QString aTypeStr=ui->typeComboBox->currentText();

    QTextLength::Type aType;

    if (aTypeStr=="VariableLength")
    {
        aType=QTextLength::VariableLength;
    }
    else
    if (aTypeStr=="FixedLength")
    {
        aType=QTextLength::FixedLength;
    }
    else
    if (aTypeStr=="PercentageLength")
    {
        aType=QTextLength::PercentageLength;
    }
    else
    {
        Q_ASSERT(false);
    }

    return QTextLength(aType, ui->valueSpinBox->value());
}

void TextLengthEditDialog::on_okButton_clicked()
{
    accept();
}

void TextLengthEditDialog::on_cancelButton_clicked()
{
    reject();
}
