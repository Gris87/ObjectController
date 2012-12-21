#include "quaternioneditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/quaternioneditdialog.h"
#include "../propertyutils.h"

QuaternionEditor::QuaternionEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
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
    updateText();
}

void QuaternionEditor::updateText()
{
    ui->valueEdit->setText(quaternionToString(mValue, mDecimals));
}

void QuaternionEditor::handleAttributes(const PropertyAttributes *aAttributes)
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

void QuaternionEditor::on_editButton_clicked()
{
    QuaternionEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
