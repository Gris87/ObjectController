#include "matrixeditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/matrixeditdialog.h"
#include "../propertyutils.h"

MatrixEditor::MatrixEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
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
    updateText();
}

void MatrixEditor::updateText()
{
    ui->valueEdit->setText(matrixToString(mValue, mDecimals));
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
        updateText();
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
