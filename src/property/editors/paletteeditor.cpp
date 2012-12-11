#include "paletteeditor.h"
#include "ui_paletteeditor.h"

#include "../dialogs/paletteeditdialog.h"

PaletteEditor::PaletteEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::PaletteEditor)
{
    ui->setupUi(this);

    mAttributes=0;

    ui->valueEdit->setText("Palette");
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
}

void PaletteEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToPalette(ui->valueEdit);
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
