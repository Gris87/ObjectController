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
}

void IntegerEditor::setValue(const quint8 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
}

void IntegerEditor::setValue(const qint16 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
}

void IntegerEditor::setValue(const quint16 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
}

void IntegerEditor::setValue(const qint32 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
}

void IntegerEditor::setValue(const quint32 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
}

void IntegerEditor::setValue(const qint64 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
}

void IntegerEditor::setValue(const quint64 &aValue)
{
    ui->valueSpinBox->setValue(aValue);
}
