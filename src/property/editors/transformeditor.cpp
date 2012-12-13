#include "transformeditor.h"
#include "ui_transformeditor.h"

#include "../dialogs/transformeditdialog.h"
#include "../propertyutils.h"

TransformEditor::TransformEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::TransformEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

TransformEditor::~TransformEditor()
{
    delete ui;
}

void TransformEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void TransformEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void TransformEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void TransformEditor::setValue(const QTransform &aValue)
{
    mValue=aValue;
    updateUI();
}

void TransformEditor::updateUI()
{
    ui->valueEdit->setText(
                           "[("+
                           doubleToString(mValue.m11(), mDecimals)+
                           ", "+
                           doubleToString(mValue.m12(), mDecimals)+
                           ", "+
                           doubleToString(mValue.m13(), mDecimals)+
                           "), ("+
                           doubleToString(mValue.m21(), mDecimals)+
                           ", "+
                           doubleToString(mValue.m22(), mDecimals)+
                           ", "+
                           doubleToString(mValue.m23(), mDecimals)+
                           "), ("+
                           doubleToString(mValue.m31(), mDecimals)+
                           ", "+
                           doubleToString(mValue.m32(), mDecimals)+
                           ", "+
                           doubleToString(mValue.m33(), mDecimals)+
                           ")]"
                          );
}

void TransformEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToPalette(ui->valueEdit);

    int aDecimals=aAttributes->intValue("decimals", mDecimals);

    if (mDecimals!=aDecimals)
    {
        mDecimals=aDecimals;
        updateUI();
    }
}

void TransformEditor::on_editButton_clicked()
{
    TransformEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
