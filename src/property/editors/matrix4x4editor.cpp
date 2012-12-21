#include "matrix4x4editor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/matrix4x4editdialog.h"
#include "../propertyutils.h"

Matrix4x4Editor::Matrix4x4Editor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

Matrix4x4Editor::~Matrix4x4Editor()
{
    delete ui;
}

void Matrix4x4Editor::putFocus()
{
    ui->valueEdit->setFocus();
}

void Matrix4x4Editor::selectText()
{
    ui->valueEdit->selectAll();
}

void Matrix4x4Editor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void Matrix4x4Editor::setValue(const QMatrix4x4 &aValue)
{
    mValue=aValue;
    updateText();
}

void Matrix4x4Editor::updateText()
{
    ui->valueEdit->setText(matrix4x4ToString(mValue, mDecimals));
}

void Matrix4x4Editor::handleAttributes(const PropertyAttributes *aAttributes)
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

void Matrix4x4Editor::on_editButton_clicked()
{
    Matrix4x4EditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
