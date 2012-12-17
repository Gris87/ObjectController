#include "easingcurveeditor.h"
#include "ui_dialogeditor.h"

#include <QMetaEnum>

#include "../dialogs/easingcurveeditdialog.h"

EasingCurveEditor::EasingCurveEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
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

    QMetaEnum aEnum=mValue.staticMetaObject.enumerator(mValue.staticMetaObject.indexOfEnumerator("Type"));
    ui->valueEdit->setText(aEnum.valueToKey(mValue.type()));
}

void EasingCurveEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
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
