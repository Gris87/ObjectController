#include "doubleframe.h"
#include "ui_doubleframe.h"

DoubleFrame::DoubleFrame(const PropertyAttributes *aAttributes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoubleFrame)
{
    ui->setupUi(this);

    if (aAttributes)
    {
        aAttributes->applyToDoubleSpinBox(ui->valueSpinBox);
    }
}

DoubleFrame::~DoubleFrame()
{
    delete ui;
}

void DoubleFrame::setUpEnabled(bool aEnabled)
{
    ui->upToolButton->setEnabled(aEnabled);
}

void DoubleFrame::setDownEnabled(bool aEnabled)
{
    ui->downToolButton->setEnabled(aEnabled);
}

double DoubleFrame::value() const
{
    return ui->valueSpinBox->value();
}

void DoubleFrame::setValue(const double &aValue)
{
    ui->valueSpinBox->setValue(aValue);
}

void DoubleFrame::on_downToolButton_clicked()
{
    emit downPressed();
}

void DoubleFrame::on_upToolButton_clicked()
{
    emit upPressed();
}

void DoubleFrame::on_delToolButton_clicked()
{
    emit deletePressed();
}

void DoubleFrame::on_valueSpinBox_valueChanged(double aValue)
{
    emit valueChanged(aValue);
}
