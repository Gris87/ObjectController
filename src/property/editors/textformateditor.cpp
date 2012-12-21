#include "textformateditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/textformateditdialog.h"
#include "../propertyutils.h"

TextFormatEditor::TextFormatEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
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

    ui->valueEdit->setText(textFormatToString(mValue));
}

void TextFormatEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void TextFormatEditor::on_editButton_clicked()
{
    TextFormatEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
