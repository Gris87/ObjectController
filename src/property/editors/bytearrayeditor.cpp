#include "bytearrayeditor.h"
#include "ui_bytearrayeditor.h"

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
    ui->valueEdit->setText(aValue.toHex().toUpper());
}
