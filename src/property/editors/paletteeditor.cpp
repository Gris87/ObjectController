#include "paletteeditor.h"
#include "ui_paletteeditor.h"

#include "../dialogs/paletteeditdialog.h"

PaletteEditor::PaletteEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::PaletteEditor)
{
    ui->setupUi(this);
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

    ui->valueEdit->setText("Palette");
}

void PaletteEditor::on_editButton_clicked()
{
    PaletteEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
