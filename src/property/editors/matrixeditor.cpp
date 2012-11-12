#include "matrixeditor.h"
#include "ui_matrixeditor.h"

#include "../dialogs/matrixeditdialog.h"

MatrixEditor::MatrixEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::MatrixEditor)
{
    ui->setupUi(this);
}

MatrixEditor::~MatrixEditor()
{
    delete ui;
}

void MatrixEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void MatrixEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void MatrixEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void MatrixEditor::setValue(const QMatrix &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           "[("+
                           QString::number(mValue.m11())+
                           ", "+
                           QString::number(mValue.m12())+
                           "), ("+
                           QString::number(mValue.m21())+
                           ", "+
                           QString::number(mValue.m22())+
                           "); ("+
                           QString::number(mValue.dx())+
                           ", "+
                           QString::number(mValue.dy())+
                           ")]"
                          );
}

void MatrixEditor::on_editButton_clicked()
{
    MatrixEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
