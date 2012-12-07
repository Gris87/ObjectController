#include "rectfeditor.h"
#include "ui_rectfeditor.h"

#include "../dialogs/rectfeditdialog.h"
#include "../propertyutils.h"

RectFEditor::RectFEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::RectFEditor)
{
    ui->setupUi(this);

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
    ui->valueEdit->setText(
                           "[("+
                           doubleToString(mValue.x(), mDecimals)+
                           ", "+
                           doubleToString(mValue.y(), mDecimals)+
                           "), "+
                           doubleToString(mValue.width(), mDecimals)+
                           " x "+
                           doubleToString(mValue.height(), mDecimals)+
                           "]"
                          );
}

void RectFEditor::handleAttributes(const PropertyAttributes &aAttributes)
{
    int aDecimals=aAttributes.intValue("decimals", mDecimals);

    if (mDecimals!=aDecimals)
    {
        mDecimals=aDecimals;
        updateUI();
    }
}

void RectFEditor::on_editButton_clicked()
{
    RectFEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
