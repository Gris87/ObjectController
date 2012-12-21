#include "vector2deditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/vector2deditdialog.h"
#include "../propertyutils.h"

Vector2DEditor::Vector2DEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

Vector2DEditor::~Vector2DEditor()
{
    delete ui;
}

void Vector2DEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void Vector2DEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void Vector2DEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void Vector2DEditor::setValue(const QVector2D &aValue)
{
    mValue=aValue;
    updateText();
}

void Vector2DEditor::updateText()
{
    ui->valueEdit->setText(vector2DToString(mValue, mDecimals));
}

void Vector2DEditor::handleAttributes(const PropertyAttributes *aAttributes)
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

void Vector2DEditor::on_editButton_clicked()
{
    Vector2DEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
