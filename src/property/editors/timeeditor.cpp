#include "timeeditor.h"
#include "ui_timeeditor.h"

TimeEditor::TimeEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::TimeEditor)
{
    ui->setupUi(this);
}

TimeEditor::~TimeEditor()
{
    delete ui;
}

void TimeEditor::putFocus()
{
    ui->valueTimeEdit->setFocus();
}

void TimeEditor::selectText()
{
    ui->valueTimeEdit->selectAll();
}

void TimeEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void TimeEditor::setValue(const QTime &aValue)
{
    ui->valueTimeEdit->setTime(aValue);
}

void TimeEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);

    aAttributes->applyToTimeEdit(ui->valueTimeEdit);
}

void TimeEditor::on_valueTimeEdit_timeChanged(const QTime &aValue)
{
    modificationDone(aValue);
}
