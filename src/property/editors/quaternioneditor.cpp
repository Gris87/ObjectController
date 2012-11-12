#include "quaternioneditor.h"
#include "ui_quaternioneditor.h"

#include "../dialogs/quaternioneditdialog.h"

QuaternionEditor::QuaternionEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::QuaternionEditor)
{
    ui->setupUi(this);
}

QuaternionEditor::~QuaternionEditor()
{
    delete ui;
}

void QuaternionEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void QuaternionEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void QuaternionEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void QuaternionEditor::setValue(const QQuaternion &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           "["+
                           QString::number(aValue.scalar())+
                           "; "+
                           QString::number(aValue.x())+
                           ", "+
                           QString::number(aValue.y())+
                           ", "+
                           QString::number(aValue.z())+
                           "]"
                          );
}

void QuaternionEditor::on_editButton_clicked()
{
    QuaternionEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
