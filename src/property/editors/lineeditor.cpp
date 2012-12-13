#include "lineeditor.h"
#include "ui_lineeditor.h"

#include "../dialogs/lineeditdialog.h"

LineEditor::LineEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::LineEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

LineEditor::~LineEditor()
{
    delete ui;
}

void LineEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void LineEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void LineEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void LineEditor::setValue(const QLine &aValue)
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

void LineEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void LineEditor::on_editButton_clicked()
{
    LineEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
