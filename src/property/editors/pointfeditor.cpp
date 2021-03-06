#include "pointfeditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/pointfeditdialog.h"
#include "../propertyutils.h"

PointFEditor::PointFEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

PointFEditor::~PointFEditor()
{
    delete ui;
}

void PointFEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void PointFEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void PointFEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void PointFEditor::setValue(const QPointF &aValue)
{
    mValue=aValue;
    updateText();
}

void PointFEditor::updateText()
{
    ui->valueEdit->setText(pointFToString(mValue, mDecimals));
}

void PointFEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);

    int aDecimals=aAttributes->intValue("decimals", mDecimals);

    if (mDecimals!=aDecimals)
    {
        mDecimals=aDecimals;
        updateText();
    }
}

void PointFEditor::on_editButton_clicked()
{
    PointFEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
