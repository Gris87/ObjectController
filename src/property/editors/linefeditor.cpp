#include "linefeditor.h"
#include "ui_linefeditor.h"

#include "../dialogs/linefeditdialog.h"

LineFEditor::LineFEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::LineFEditor)
{
    ui->setupUi(this);
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
                           QString::number(mValue.x1())+
                           ", "+
                           QString::number(mValue.y1())+
                           "), ("+
                           QString::number(mValue.x2())+
                           ", "+
                           QString::number(mValue.y2())+
                           ")]"
                          );
}

void LineFEditor::on_editButton_clicked()
{
    LineFEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
