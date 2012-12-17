#include "textlengtheditdialog.h"
#include "ui_textlengtheditdialog.h"

TextLengthEditDialog::TextLengthEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextLengthEditDialog)
{
    init(QTextLength(), 0);
}

TextLengthEditDialog::TextLengthEditDialog(QTextLength aTextLength, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextLengthEditDialog)
{
    init(aTextLength, 0);
}

TextLengthEditDialog::TextLengthEditDialog(const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextLengthEditDialog)
{
    init(QTextLength(), aAttributes);
}

TextLengthEditDialog::TextLengthEditDialog(QTextLength aTextLength, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextLengthEditDialog)
{
    init(aTextLength, aAttributes);
}

void TextLengthEditDialog::init(QTextLength aTextLength, const PropertyAttributes *aAttributes)
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

    if (aAttributes)
    {
        aAttributes->applyToCombobox(ui->typeComboBox);
        aAttributes->applyToDoubleSpinBox(ui->valueSpinBox);

        ui->typeComboBox->setEnabled(aAttributes->boolValue("allowSetLengthType", ui->typeComboBox->isEnabled()));
    }
}

TextLengthEditDialog::~TextLengthEditDialog()
{
    delete ui;
}

QTextLength TextLengthEditDialog::resultValue()
{
    QString aTypeStr=ui->typeComboBox->currentText();

    QTextLength::Type aType=QTextLength::VariableLength;

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
