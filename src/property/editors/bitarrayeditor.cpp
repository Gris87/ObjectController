#include "bitarrayeditor.h"
#include "ui_bitarrayeditor.h"

#include "../dialogs/bitarrayeditdialog.h"

BitArrayEditor::BitArrayEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::BitArrayEditor)
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

    QString res;

    for (int i=0; i<mValue.count(); ++i)
    {
        res.append(mValue.at(i) ? "1" : "0");
    }

    ui->valueEdit->setText(res);
}

void BitArrayEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToPalette(ui->valueEdit);
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
