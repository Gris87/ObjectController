#include "dateeditor.h"
#include "ui_dateeditor.h"

DateEditor::DateEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DateEditor)
{
    ui->setupUi(this);
}

DateEditor::~DateEditor()
{
    delete ui;
}

void DateEditor::putFocus()
{
    ui->valueDateEdit->setFocus();
}

void DateEditor::selectText()
{
    ui->valueDateEdit->selectAll();
}

void DateEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void DateEditor::setValue(const QDate &aValue)
{
    ui->valueDateEdit->setDate(aValue);
}

void DateEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);

    ui->valueDateEdit->setToolTip(      aAttributes->stringValue("toolTip",       ui->valueDateEdit->toolTip()));
    ui->valueDateEdit->setMinimumDate(  aAttributes->dateValue(  "minDate",       ui->valueDateEdit->minimumDate()));
    ui->valueDateEdit->setMaximumDate(  aAttributes->dateValue(  "maxDate",       ui->valueDateEdit->maximumDate()));
    ui->valueDateEdit->setDisplayFormat(aAttributes->stringValue("displayFormat", ui->valueDateEdit->displayFormat()));
    ui->valueDateEdit->setCalendarPopup(aAttributes->boolValue(  "calendarPopup", ui->valueDateEdit->calendarPopup()));
}

void DateEditor::on_valueDateEdit_dateChanged(const QDate &aValue)
{
    modificationDone(aValue);
}
