#include "rectfeditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/rectfeditdialog.h"
#include "../propertyutils.h"

RectFEditor::RectFEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

RectFEditor::~RectFEditor()
{
    delete ui;
}

void RectFEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void RectFEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void RectFEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void RectFEditor::setValue(const QRectF &aValue)
{
    mValue=aValue;
    updateUI();
}

void RectFEditor::updateUI()
{
    ui->valueEdit->setText(rectfToString(mValue, mDecimals));
}

void RectFEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);

    int aDecimals=aAttributes->intValue("decimals", mDecimals);

    if (mDecimals!=aDecimals)
    {
        mDecimals=aDecimals;
        updateUI();
    }
}

void RectFEditor::on_editButton_clicked()
{
    RectFEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
