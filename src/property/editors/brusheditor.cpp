#include "brusheditor.h"
#include "ui_dialogeditor.h"

#include <QPainter>
#include <QMetaEnum>

#include "../dialogs/brusheditdialog.h"
#include "../propertyutils.h"

BrushEditor::BrushEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mAlphaEnabled=true;
    mDecimals=6;
}

BrushEditor::~BrushEditor()
{
    delete ui;
}

void BrushEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void BrushEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void BrushEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void BrushEditor::setValue(const QBrush &aValue)
{
    mValue=aValue;

    updateText();
    setIcon(iconForBrush(mValue));
}

void BrushEditor::updateText()
{
    ui->valueEdit->setText(brushToString(mValue, mAlphaEnabled, mDecimals));
}

void BrushEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);

    bool needUpdate=false;



    bool aAlphaEnabled=aAttributes->boolValue("alphaEnabled", mAlphaEnabled);

    if (mAlphaEnabled!=aAlphaEnabled)
    {
        mAlphaEnabled=aAlphaEnabled;
        needUpdate=true;
    }



    int aDecimals=aAttributes->intValue("decimals", mDecimals);

    if (mDecimals!=aDecimals)
    {
        mDecimals=aDecimals;
        needUpdate=true;
    }



    if (needUpdate)
    {
        updateText();
    }
}

void BrushEditor::on_editButton_clicked()
{
    BrushEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
