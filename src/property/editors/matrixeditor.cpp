#include "matrixeditor.h"
#include "ui_matrixeditor.h"

#include "../dialogs/matrixeditdialog.h"
#include "../propertyutils.h"

MatrixEditor::MatrixEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::MatrixEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

MatrixEditor::~MatrixEditor()
{
    delete ui;
}

void MatrixEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void MatrixEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void MatrixEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void MatrixEditor::setValue(const QMatrix &aValue)
{
    mValue=aValue;
    updateUI();
}

void MatrixEditor::updateUI()
{
    ui->valueEdit->setText(
                           "[("+
                           doubleToString(mValue.m11(), mDecimals)+
                           ", "+
                           doubleToString(mValue.m12(), mDecimals)+
                           "), ("+
                           doubleToString(mValue.m21(), mDecimals)+
                           ", "+
                           doubleToString(mValue.m22(), mDecimals)+
                           "); ("+
                           doubleToString(mValue.dx(), mDecimals)+
                           ", "+
                           doubleToString(mValue.dy(), mDecimals)+
                           ")]"
                          );
}

void MatrixEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);

    int aDecimals=aAttributes->intValue("decimals", mDecimals);

    if (mDecimals!=aDecimals)
    {
        mDecimals=aDecimals;
        updateUI();
    }
}

void MatrixEditor::on_editButton_clicked()
{
    MatrixEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
