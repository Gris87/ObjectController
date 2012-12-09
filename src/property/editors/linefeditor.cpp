#include "linefeditor.h"
#include "ui_linefeditor.h"

#include "../dialogs/linefeditdialog.h"
#include "../propertyutils.h"

LineFEditor::LineFEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::LineFEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

LineFEditor::~LineFEditor()
{
    delete ui;
}

void LineFEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void LineFEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void LineFEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void LineFEditor::setValue(const QLineF &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           "[("+
                           doubleToString(mValue.x1(), mDecimals)+
                           ", "+
                           doubleToString(mValue.y1(), mDecimals)+
                           "), ("+
                           doubleToString(mValue.x2(), mDecimals)+
                           ", "+
                           doubleToString(mValue.y2(), mDecimals)+
                           ")]"
                          );
}

void LineFEditor::on_editButton_clicked()
{
    LineFEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
