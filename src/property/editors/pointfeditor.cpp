#include "pointfeditor.h"
#include "ui_pointfeditor.h"

#include "../dialogs/pointfeditdialog.h"
#include "../propertyutils.h"

PointFEditor::PointFEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::PointFEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
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
                           doubleToString(mValue.x(), mDecimals)+
                           ", "+
                           doubleToString(mValue.y(), mDecimals)+
                           ")"
                          );
}

void PointFEditor::on_editButton_clicked()
{
    PointFEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
