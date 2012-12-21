#include "textlengtheditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/textlengtheditdialog.h"
#include "propertyutils.h"

TextLengthEditor::TextLengthEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
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
    updateUI();
}

void TextLengthEditor::updateUI()
{
    ui->valueEdit->setText(textLengthToString(mValue));
}

void TextLengthEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);

    int aDecimals=aAttributes->intValue("decimals", mDecimals);

    if (mDecimals!=aDecimals)
    {
        mDecimals=aDecimals;
        updateUI();
    }
}

void TextLengthEditor::on_editButton_clicked()
{
    TextLengthEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
