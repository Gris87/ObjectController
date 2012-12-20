#include "bitarrayeditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/bitarrayeditdialog.h"
#include "../propertyutils.h"

BitArrayEditor::BitArrayEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);
    mAttributes=0;
}

BitArrayEditor::~BitArrayEditor()
{
    delete ui;
}

void BitArrayEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void BitArrayEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void BitArrayEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void BitArrayEditor::setValue(const QBitArray &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(bitArrayToString(mValue));
}

void BitArrayEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void BitArrayEditor::on_editButton_clicked()
{
    BitArrayEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
