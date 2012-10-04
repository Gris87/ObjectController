#include "booleditor.h"
#include "ui_booleditor.h"

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
    ui->valueCheckBox->setChecked(aValue);
}

void BoolEditor::on_valueCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->valueCheckBox->setText(tr("true"));
    }
    else
    {
        ui->valueCheckBox->setText(tr("false"));
    }

    if (mCanEmitValueChangedSignal)
    {
        emit valueChanged(checked);
    }
}
