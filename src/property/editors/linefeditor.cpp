#include "linefeditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/linefeditdialog.h"
#include "../propertyutils.h"

LineFEditor::LineFEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

LineFEditor::~LineFEditor()
{
    delete ui;
}

void LineFEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void LineFEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void LineFEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void LineFEditor::setValue(const QLineF &aValue)
{
    mValue=aValue;
    updateUI();
}

void LineFEditor::updateUI()
{
    ui->valueEdit->setText(lineFToString(mValue, mDecimals));
}

void LineFEditor::handleAttributes(const PropertyAttributes *aAttributes)
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

void LineFEditor::on_editButton_clicked()
{
    LineFEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
