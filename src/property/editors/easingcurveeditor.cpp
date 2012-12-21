#include "easingcurveeditor.h"
#include "ui_dialogeditor.h"

#include <QMetaEnum>

#include "../dialogs/easingcurveeditdialog.h"
#include "../propertyutils.h"

EasingCurveEditor::EasingCurveEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
    mDecimals=6;
}

EasingCurveEditor::~EasingCurveEditor()
{
    delete ui;
}

void EasingCurveEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void EasingCurveEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void EasingCurveEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void EasingCurveEditor::setValue(const QEasingCurve &aValue)
{
    mValue=aValue;
    updateUI();
}

void EasingCurveEditor::updateUI()
{
    ui->valueEdit->setText(easingCurveToString(mValue, mDecimals));
}

void EasingCurveEditor::handleAttributes(const PropertyAttributes *aAttributes)
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

void EasingCurveEditor::on_editButton_clicked()
{
    EasingCurveEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
