#include "doubleeditor.h"
#include "ui_doubleeditor.h"

DoubleEditor::DoubleEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DoubleEditor)
{
    ui->setupUi(this);
}

DoubleEditor::~DoubleEditor()
{
    delete ui;
}

void DoubleEditor::putFocus()
{
    ui->valueSpinBox->setFocus();
}

void DoubleEditor::selectText()
{
    ui->valueSpinBox->selectAll();
}

void DoubleEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void DoubleEditor::setValue(const double &aValue)
{
    ui->valueSpinBox->setValue(aValue);
    ui->valueSpinBox->setMinimum(-DBL_MAX);
    ui->valueSpinBox->setMaximum(DBL_MAX);
}

void DoubleEditor::setValue(const float &aValue)
{
    ui->valueSpinBox->setValue(aValue);
    ui->valueSpinBox->setMinimum(-FLT_MAX);
    ui->valueSpinBox->setMaximum(FLT_MAX);
}

void DoubleEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    ui->valueSpinBox->setToolTip(    aAttributes->stringValue("toolTip",     ui->valueSpinBox->toolTip()));
    ui->valueSpinBox->setWrapping(   aAttributes->boolValue(  "wrapping",    ui->valueSpinBox->wrapping()));
    ui->valueSpinBox->setAccelerated(aAttributes->boolValue(  "accelerated", ui->valueSpinBox->isAccelerated()));
    ui->valueSpinBox->setPrefix(     aAttributes->stringValue("prefix",      ui->valueSpinBox->prefix()));
    ui->valueSpinBox->setSuffix(     aAttributes->stringValue("suffix",      ui->valueSpinBox->suffix()));
    ui->valueSpinBox->setMinimum(    aAttributes->doubleValue("minValue",    ui->valueSpinBox->minimum()));
    ui->valueSpinBox->setMaximum(    aAttributes->doubleValue("maxValue",    ui->valueSpinBox->maximum()));
    ui->valueSpinBox->setDecimals(   aAttributes->intValue(   "decimals",    ui->valueSpinBox->decimals()));
    ui->valueSpinBox->setSingleStep( aAttributes->doubleValue("step",        ui->valueSpinBox->singleStep()));
}

void DoubleEditor::on_valueSpinBox_valueChanged(double aValue)
{
    modificationDone(aValue);
}
