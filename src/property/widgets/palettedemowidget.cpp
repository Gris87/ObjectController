#include "palettedemowidget.h"
#include "ui_palettedemowidget.h"

PaletteDemoWidget::PaletteDemoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaletteDemoWidget)
{
    ui->setupUi(this);
}

PaletteDemoWidget::~PaletteDemoWidget()
{
    delete ui;
}
