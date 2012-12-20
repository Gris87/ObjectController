#include "booleditor.h"
#include "ui_booleditor.h"

#include "../propertyutils.h"

BoolEditor::BoolEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::BoolEditor)
{
    ui->setupUi(this);
}

BoolEditor::~BoolEditor()
{
    delete ui;
}

void BoolEditor::putFocus()
{
    ui->valueCheckBox->setFocus();
}

void BoolEditor::setValue(const bool &aValue)
{
    ui->valueCheckBox->blockSignals(true);

    ui->valueCheckBox->setChecked(aValue);
    ui->valueCheckBox->setText(boolToString(aValue));

    ui->valueCheckBox->blockSignals(false);
}

void BoolEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);

    aAttributes->applyToCheckBox(ui->valueCheckBox);
}

void BoolEditor::on_valueCheckBox_toggled(bool checked)
{
    setValue(checked);
    emit valueChanged(checked);
}
