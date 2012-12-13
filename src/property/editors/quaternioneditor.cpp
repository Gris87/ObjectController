#include "quaternioneditor.h"
#include "ui_quaternioneditor.h"

#include "../dialogs/quaternioneditdialog.h"
#include "../propertyutils.h"

QuaternionEditor::QuaternionEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::QuaternionEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

QuaternionEditor::~QuaternionEditor()
{
    delete ui;
}

void QuaternionEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void QuaternionEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void QuaternionEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void QuaternionEditor::setValue(const QQuaternion &aValue)
{
    mValue=aValue;
}

void QuaternionEditor::updateUI()
{
    ui->valueEdit->setText(
                           "["+
                           doubleToString(mValue.scalar(), mDecimals)+
                           "; "+
                           doubleToString(mValue.x(), mDecimals)+
                           ", "+
                           doubleToString(mValue.y(), mDecimals)+
                           ", "+
                           doubleToString(mValue.z(), mDecimals)+
                           "]"
                          );
}

void QuaternionEditor::handleAttributes(const PropertyAttributes *aAttributes)
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

void QuaternionEditor::on_editButton_clicked()
{
    QuaternionEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
