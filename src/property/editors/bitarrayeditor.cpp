#include "bitarrayeditor.h"
#include "ui_bitarrayeditor.h"

BitArrayEditor::BitArrayEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::BitArrayEditor)
{
    ui->setupUi(this);
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
    QString res;

    for (int i=0; i<aValue.count(); ++i)
    {
        res.append(aValue.at(i) ? "1" : "0");
    }

    ui->valueEdit->setText(res);
}
