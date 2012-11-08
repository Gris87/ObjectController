#include "pointfeditor.h"
#include "ui_pointfeditor.h"

#include "../dialogs/pointfeditdialog.h"

PointFEditor::PointFEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::PointFEditor)
{
    ui->setupUi(this);
}

PointFEditor::~PointFEditor()
{
    delete ui;
}

void PointFEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void PointFEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void PointFEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void PointFEditor::setValue(const QPointF &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           "("+
                           QString::number(mValue.x())+
                           ", "+
                           QString::number(mValue.y())+
                           ")"
                          );
}

void PointFEditor::on_editButton_clicked()
{
    PointFEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
