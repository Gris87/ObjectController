#include "keysequenceeditor.h"
#include "ui_keysequenceeditor.h"

#include "../dialogs/keysequenceeditdialog.h"

KeySequenceEditor::KeySequenceEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::KeySequenceEditor)
{
    ui->setupUi(this);
}

KeySequenceEditor::~KeySequenceEditor()
{
    delete ui;
}

void KeySequenceEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void KeySequenceEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void KeySequenceEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void KeySequenceEditor::setValue(const QKeySequence &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(mValue.toString());
}

void KeySequenceEditor::on_editButton_clicked()
{
    KeySequenceEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
