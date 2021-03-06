#include "transformeditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/transformeditdialog.h"
#include "../propertyutils.h"

TransformEditor::TransformEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
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
    updateText();
}

void TransformEditor::updateText()
{
    ui->valueEdit->setText(transformToString(mValue, mDecimals));
}

void TransformEditor::handleAttributes(const PropertyAttributes *aAttributes)
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

void TransformEditor::on_editButton_clicked()
{
    TransformEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
