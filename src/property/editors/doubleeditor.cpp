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
}

void DoubleEditor::setValue(const float &aValue)
{
    ui->valueSpinBox->setValue(aValue);
}

void DoubleEditor::on_valueSpinBox_valueChanged(double aValue)
{
    if (mCanEmitValueChangedSignal)
    {
        emit valueChanged(aValue);
    }
}
