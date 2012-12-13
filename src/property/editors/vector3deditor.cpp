#include "vector3deditor.h"
#include "ui_vector3deditor.h"

#include "../dialogs/vector3deditdialog.h"
#include "../propertyutils.h"

Vector3DEditor::Vector3DEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::Vector3DEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

Vector3DEditor::~Vector3DEditor()
{
    delete ui;
}

void Vector3DEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void Vector3DEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void Vector3DEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void Vector3DEditor::setValue(const QVector3D &aValue)
{
    mValue=aValue;
}

void Vector3DEditor::updateUI()
{
    ui->valueEdit->setText(
                           "["+
                           doubleToString(aValue.x(), mDecimals)+
                           ", "+
                           doubleToString(aValue.y(), mDecimals)+
                           ", "+
                           doubleToString(aValue.z(), mDecimals)+
                           "]"
                          );
}

void Vector3DEditor::handleAttributes(const PropertyAttributes *aAttributes)
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

void Vector3DEditor::on_editButton_clicked()
{
    Vector3DEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
