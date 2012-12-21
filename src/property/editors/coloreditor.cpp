#include "coloreditor.h"
#include "ui_dialogeditor.h"

#include <QPainter>

#include "../dialogs/coloreditdialog.h"
#include "../propertyutils.h"

ColorEditor::ColorEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mAlphaEnabled=true;
}

ColorEditor::~ColorEditor()
{
    delete ui;
}

void ColorEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void ColorEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void ColorEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void ColorEditor::setValue(const QColor &aValue)
{
    mValue=aValue;

    updateText();
    setIcon(iconForColor(mValue));
}

void ColorEditor::updateText()
{
    ui->valueEdit->setText(colorToString(mValue, mAlphaEnabled));
}

void ColorEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);

    bool aAlphaEnabled=aAttributes->boolValue("alphaEnabled", mAlphaEnabled);

    if (mAlphaEnabled!=aAlphaEnabled)
    {
        mAlphaEnabled=aAlphaEnabled;
        updateText();
    }
}

void ColorEditor::on_editButton_clicked()
{
    ColorEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.selectedColor());
        emit valueChanged(mValue);
    }
}
