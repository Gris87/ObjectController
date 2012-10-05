#include "bytearrayeditor.h"
#include "ui_bytearrayeditor.h"

#include "../dialogs/bytearrayeditdialog.h"

ByteArrayEditor::ByteArrayEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::ByteArrayEditor)
{
    ui->setupUi(this);
}

ByteArrayEditor::~ByteArrayEditor()
{
    delete ui;
}

void ByteArrayEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void ByteArrayEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void ByteArrayEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void ByteArrayEditor::setValue(const QByteArray &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(mValue.toHex().toUpper());
}

void ByteArrayEditor::on_editButton_clicked()
{
    ByteArrayEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
