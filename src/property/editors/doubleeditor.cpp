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
    CustomEditor::handleAttributes(aAttributes);

    aAttributes->applyToDoubleSpinBox(ui->valueSpinBox);
}

void DoubleEditor::on_valueSpinBox_valueChanged(double aValue)
{
    modificationDone(aValue);
}
