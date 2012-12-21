#include "paletteeditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/paletteeditdialog.h"
#include "../propertyutils.h"

PaletteEditor::PaletteEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mAlphaEnabled=true;
}

PaletteEditor::~PaletteEditor()
{
    delete ui;
}

void PaletteEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void PaletteEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void PaletteEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void PaletteEditor::setValue(const QPalette &aValue)
{
    mValue=aValue;
    updateText();
}

void PaletteEditor::updateText()
{
    ui->valueEdit->setText(paletteToString(mValue, mAlphaEnabled));
}

void PaletteEditor::handleAttributes(const PropertyAttributes *aAttributes)
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

void PaletteEditor::on_editButton_clicked()
{
    PaletteEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
