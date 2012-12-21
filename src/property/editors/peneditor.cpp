#include "peneditor.h"
#include "ui_dialogeditor.h"

#include <QPainter>

#include "../dialogs/peneditdialog.h"
#include "../propertyutils.h"

PenEditor::PenEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mAlphaEnabled=true;
    mDecimals=6;
}

PenEditor::~PenEditor()
{
    delete ui;
}

void PenEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void PenEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void PenEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void PenEditor::setValue(const QPen &aValue)
{
    mValue=aValue;

    updateText();
    setIcon(iconForPen(mValue));
}

void PenEditor::updateText()
{
    ui->valueEdit->setText(penToString(mValue, mAlphaEnabled, mDecimals));
}

void PenEditor::handleAttributes(const PropertyAttributes *aAttributes)
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

void PenEditor::on_editButton_clicked()
{
    PenEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
