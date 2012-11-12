#include "vector3deditor.h"
#include "ui_vector3deditor.h"

#include "../dialogs/vector3deditdialog.h"

Vector3DEditor::Vector3DEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::Vector3DEditor)
{
    ui->setupUi(this);
}

Vector3DEditor::~Vector3DEditor()
{
    delete ui;
}

void Vector3DEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void Vector3DEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void Vector3DEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void Vector3DEditor::setValue(const QVector3D &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           "["+
                           QString::number(aValue.x())+
                           ", "+
                           QString::number(aValue.y())+
                           ", "+
                           QString::number(aValue.z())+
                           "]"
                          );
}

void Vector3DEditor::on_editButton_clicked()
{
    Vector3DEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
