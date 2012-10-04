#include "stringeditor.h"
#include "ui_stringeditor.h"

StringEditor::StringEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::StringEditor)
{
    ui->setupUi(this);
}

StringEditor::~StringEditor()
{
    delete ui;
}

void StringEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void StringEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void StringEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void StringEditor::setValue(const QString &aValue)
{
    ui->valueEdit->setText(aValue);
}

void StringEditor::on_valueEdit_textEdited(const QString &aValue)
{
    modificationDone(aValue);
}
