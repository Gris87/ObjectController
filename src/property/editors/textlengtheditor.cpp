#include "textlengtheditor.h"
#include "ui_textlengtheditor.h"

#include "../dialogs/textlengtheditdialog.h"

TextLengthEditor::TextLengthEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::TextLengthEditor)
{
    ui->setupUi(this);
}

TextLengthEditor::~TextLengthEditor()
{
    delete ui;
}

void TextLengthEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void TextLengthEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void TextLengthEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void TextLengthEditor::setValue(const QTextLength &aValue)
{
    mValue=aValue;



    QString res="[";

    switch (mValue.type())
    {
        case QTextLength::VariableLength:   res.append("VariableLength");   break;
        case QTextLength::FixedLength:      res.append("FixedLength");      break;
        case QTextLength::PercentageLength: res.append("PercentageLength"); break;
    }

    res.append(", ");
    res.append(QString::number(mValue.rawValue()));
    res.append("]");

    ui->valueEdit->setText(res);
}

void TextLengthEditor::on_editButton_clicked()
{
    TextLengthEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
