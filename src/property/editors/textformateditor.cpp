#include "textformateditor.h"
#include "ui_textformateditor.h"

#include "../dialogs/textformateditdialog.h"

TextFormatEditor::TextFormatEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::TextFormatEditor)
{
    ui->setupUi(this);
}

TextFormatEditor::~TextFormatEditor()
{
    delete ui;
}

void TextFormatEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void TextFormatEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void TextFormatEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void TextFormatEditor::setValue(const QTextFormat &aValue)
{
    mValue=aValue;



    ui->editButton->setEnabled(true);

    QString res="[Unknown type]";

    if (aValue.isImageFormat())
    {
        res="ImageFormat";
    }
    else
    if (aValue.isTableCellFormat())
    {
        res="TableCellFormat";
    }
    else
    if (aValue.isTableFormat())
    {
        res="TableFormat";
    }
    else
    if (aValue.isBlockFormat())
    {
        res="BlockFormat";
    }
    else
    if (aValue.isCharFormat())
    {
        res="CharFormat";
    }
    else
    if (aValue.isFrameFormat())
    {
        res="FrameFormat";
    }
    else
    if (aValue.isListFormat())
    {
        res="ListFormat";
    }
    else
    {
        // TODO: Remove it when you implement ideal editor for TextFormat
        ui->editButton->setEnabled(false);
    }

    ui->valueEdit->setText(res);
}

void TextFormatEditor::on_editButton_clicked()
{
    TextFormatEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
