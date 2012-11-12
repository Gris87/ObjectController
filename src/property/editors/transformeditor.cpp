#include "transformeditor.h"
#include "ui_transformeditor.h"

#include "../dialogs/transformeditdialog.h"

TransformEditor::TransformEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::TransformEditor)
{
    ui->setupUi(this);
}

TransformEditor::~TransformEditor()
{
    delete ui;
}

void TransformEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void TransformEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void TransformEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void TransformEditor::setValue(const QTransform &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           "[("+
                           QString::number(mValue.m11())+
                           ", "+
                           QString::number(mValue.m12())+
                           ", "+
                           QString::number(mValue.m13())+
                           "), ("+
                           QString::number(mValue.m21())+
                           ", "+
                           QString::number(mValue.m22())+
                           ", "+
                           QString::number(mValue.m23())+
                           "), ("+
                           QString::number(mValue.m31())+
                           ", "+
                           QString::number(mValue.m32())+
                           ", "+
                           QString::number(mValue.m33())+
                           ")]"
                          );
}

void TransformEditor::on_editButton_clicked()
{
    TransformEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
