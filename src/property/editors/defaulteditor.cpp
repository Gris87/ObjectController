#include "defaulteditor.h"
#include "ui_defaulteditor.h"

DefaultEditor::DefaultEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DefaultEditor)
{
    ui->setupUi(this);
}

DefaultEditor::~DefaultEditor()
{
    delete ui;
}

void DefaultEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void DefaultEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void DefaultEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void DefaultEditor::setValue(const QString &aValue)
{
    ui->valueEdit->setText(aValue);
}

void DefaultEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);

    aAttributes->applyToWidget(ui->valueEdit);
}
