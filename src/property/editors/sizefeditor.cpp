#include "sizefeditor.h"
#include "ui_sizefeditor.h"

#include "../dialogs/sizefeditdialog.h"
#include "../propertyutils.h"

SizeFEditor::SizeFEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::SizeFEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

SizeFEditor::~SizeFEditor()
{
    delete ui;
}

void SizeFEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void SizeFEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void SizeFEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void SizeFEditor::setValue(const QSizeF &aValue)
{
    mValue=aValue;
    updateUI();
}

void SizeFEditor::updateUI()
{
    ui->valueEdit->setText(
                           doubleToString(mValue.width(), mDecimals)+
                           " x "+
                           doubleToString(mValue.height(), mDecimals)
                          );
}

void SizeFEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToPalette(ui->valueEdit);

    int aDecimals=aAttributes->intValue("decimals", mDecimals);

    if (mDecimals!=aDecimals)
    {
        mDecimals=aDecimals;
        updateUI();
    }
}

void SizeFEditor::on_editButton_clicked()
{
    SizeFEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
