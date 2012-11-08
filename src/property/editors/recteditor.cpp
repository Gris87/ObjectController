#include "recteditor.h"
#include "ui_recteditor.h"

#include "../dialogs/recteditdialog.h"

RectEditor::RectEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::RectEditor)
{
    ui->setupUi(this);
}

RectEditor::~RectEditor()
{
    delete ui;
}

void RectEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void RectEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void RectEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void RectEditor::setValue(const QRect &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           "[("+
                           QString::number(aValue.x())+
                           ", "+
                           QString::number(aValue.y())+
                           "), "+
                           QString::number(aValue.width())+
                           " x "+
                           QString::number(aValue.height())+
                           "]"
                          );
}

void RectEditor::on_editButton_clicked()
{
    RectEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}