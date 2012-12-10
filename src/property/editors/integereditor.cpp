#include "integereditor.h"
#include "ui_integereditor.h"

IntegerEditor::IntegerEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::IntegerEditor)
{
    ui->setupUi(this);
}

IntegerEditor::~IntegerEditor()
{
    delete ui;
}

void IntegerEditor::putFocus()
{
    ui->valueSpinBox->setFocus();
}

void IntegerEditor::selectText()
{
    ui->valueSpinBox->selectAll();
}

void IntegerEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void IntegerEditor::setValue(const qint8 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
    ui->valueSpinBox->setMinimum(SCHAR_MIN);
    ui->valueSpinBox->setMaximum(SCHAR_MAX);
}

void IntegerEditor::setValue(const quint8 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
    ui->valueSpinBox->setMinimum(0);
    ui->valueSpinBox->setMaximum(UCHAR_MAX);
}

void IntegerEditor::setValue(const qint16 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
    ui->valueSpinBox->setMinimum(SHRT_MIN);
    ui->valueSpinBox->setMaximum(SHRT_MAX);
}

void IntegerEditor::setValue(const quint16 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
    ui->valueSpinBox->setMinimum(0);
    ui->valueSpinBox->setMaximum(USHRT_MAX);
}

void IntegerEditor::setValue(const qint32 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
    ui->valueSpinBox->setMinimum(INT_MIN);
    ui->valueSpinBox->setMaximum(INT_MAX);
}

void IntegerEditor::setValue(const quint32 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
    ui->valueSpinBox->setMinimum(0);
    ui->valueSpinBox->setMaximum(INT_MAX);
}

void IntegerEditor::setValue(const qint64 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
    ui->valueSpinBox->setMinimum(INT_MIN);
    ui->valueSpinBox->setMaximum(INT_MAX);
}

void IntegerEditor::setValue(const quint64 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
    ui->valueSpinBox->setMinimum(0);
    ui->valueSpinBox->setMaximum(INT_MAX);
}

void IntegerEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);

    aAttributes->applyToSpinBox(ui->valueSpinBox);
}

void IntegerEditor::on_valueSpinBox_valueChanged(int aValue)
{
    modificationDone(aValue);
}
