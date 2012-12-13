#include "vector4deditor.h"
#include "ui_vector4deditor.h"

#include "../dialogs/vector4deditdialog.h"
#include "../propertyutils.h"

Vector4DEditor::Vector4DEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::Vector4DEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

Vector4DEditor::~Vector4DEditor()
{
    delete ui;
}

void Vector4DEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void Vector4DEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void Vector4DEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void Vector4DEditor::setValue(const QVector4D &aValue)
{
    mValue=aValue;
    updateUI();
}

void Vector4DEditor::updateUI()
{
    ui->valueEdit->setText(
                           "["+
                           doubleToString(aValue.x(), mDecimals)+
                           ", "+
                           doubleToString(aValue.y(), mDecimals)+
                           ", "+
                           doubleToString(aValue.z(), mDecimals)+
                           ", "+
                           doubleToString(aValue.w(), mDecimals)+
                           "]"
                          );
}

void Vector4DEditor::handleAttributes(const PropertyAttributes *aAttributes)
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

void Vector4DEditor::on_editButton_clicked()
{
    Vector4DEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
