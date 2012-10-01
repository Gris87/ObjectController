#include "integereditor.h"
#include "ui_integereditor.h"

IntegerEditor::IntegerEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntegerEditor)
{
    ui->setupUi(this);
}

IntegerEditor::~IntegerEditor()
{
    delete ui;
}
