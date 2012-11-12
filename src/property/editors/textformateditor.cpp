#include "textformateditor.h"
#include "ui_textformateditor.h"

#include <QMetaEnum>

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



    QMetaEnum aEnum=mValue.staticMetaObject.enumerator(mValue.staticMetaObject.indexOfEnumerator("FormatType"));
    ui->valueEdit->setText(aEnum.valueToKey(mValue.type()));
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
