#include "vector4deditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/vector4deditdialog.h"
#include "../propertyutils.h"

Vector4DEditor::Vector4DEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
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
    updateText();
}

void Vector4DEditor::updateText()
{
    ui->valueEdit->setText(vector4DToString(mValue, mDecimals));
}

void Vector4DEditor::handleAttributes(const PropertyAttributes *aAttributes)
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

void Vector4DEditor::on_editButton_clicked()
{
    Vector4DEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
