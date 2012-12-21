#include "fonteditor.h"
#include "ui_dialogeditor.h"

#include <QPainter>

#include "../dialogs/fonteditdialog.h"
#include "../propertyutils.h"

FontEditor::FontEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

FontEditor::~FontEditor()
{
    delete ui;
}

void FontEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void FontEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void FontEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void FontEditor::setValue(const QFont &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(fontToString(mValue));
    setIcon(iconForFont(mValue));
}

void FontEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void FontEditor::on_editButton_clicked()
{
    FontEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.selectedFont());
        emit valueChanged(mValue);
    }
}
