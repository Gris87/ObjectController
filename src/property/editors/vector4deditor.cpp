#include "vector4deditor.h"
#include "ui_vector4deditor.h"

#include "../dialogs/vector4deditdialog.h"

Vector4DEditor::Vector4DEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::Vector4DEditor)
{
    ui->setupUi(this);
}

Vector4DEditor::~Vector4DEditor()
{
    delete ui;
}

void Vector4DEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void Vector4DEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void Vector4DEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void Vector4DEditor::setValue(const QVector4D &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           "["+
                           QString::number(aValue.x())+
                           ", "+
                           QString::number(aValue.y())+
                           ", "+
                           QString::number(aValue.z())+
                           ", "+
                           QString::number(aValue.w())+
                           "]"
                          );
}

void Vector4DEditor::on_editButton_clicked()
{
    Vector4DEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
