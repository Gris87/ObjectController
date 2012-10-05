#include "chareditor.h"
#include "ui_chareditor.h"

CharEditor::CharEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::CharEditor)
{
    ui->setupUi(this);
}

CharEditor::~CharEditor()
{
    delete ui;
}

void CharEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void CharEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void CharEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void CharEditor::setValue(const QChar &aValue)
{
    ui->valueEdit->setText(aValue);
}

void CharEditor::on_valueEdit_textEdited(const QString &aValue)
{
    if (aValue.length()==0)
    {
        modificationDone(QChar());
    }
    else
    {
        modificationDone(aValue.at(0));
    }
}
