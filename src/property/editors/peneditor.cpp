#include "peneditor.h"
#include "ui_peneditor.h"

#include "../dialogs/peneditdialog.h"

PenEditor::PenEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::PenEditor)
{
    ui->setupUi(this);

    ui->valueEdit->setText("Pen");
}

PenEditor::~PenEditor()
{
    delete ui;
}

void PenEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void PenEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void PenEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void PenEditor::setValue(const QPen &aValue)
{
    mValue=aValue;


}

void PenEditor::on_editButton_clicked()
{
    PenEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
