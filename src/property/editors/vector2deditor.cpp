#include "vector2deditor.h"
#include "ui_vector2deditor.h"

#include "../dialogs/vector2deditdialog.h"

Vector2DEditor::Vector2DEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::Vector2DEditor)
{
    ui->setupUi(this);
}

Vector2DEditor::~Vector2DEditor()
{
    delete ui;
}

void Vector2DEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void Vector2DEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void Vector2DEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void Vector2DEditor::setValue(const QVector2D &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           "["+
                           QString::number(mValue.x())+
                           ", "+
                           QString::number(mValue.y())+
                           "]"
                          );
}

void Vector2DEditor::on_editButton_clicked()
{
    Vector2DEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
