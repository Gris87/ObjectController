#include "datetimeeditor.h"
#include "ui_datetimeeditor.h"

DateTimeEditor::DateTimeEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DateTimeEditor)
{
    ui->setupUi(this);
}

DateTimeEditor::~DateTimeEditor()
{
    delete ui;
}

void DateTimeEditor::putFocus()
{
    ui->valueDateTimeEdit->setFocus();
}

void DateTimeEditor::selectText()
{
    ui->valueDateTimeEdit->selectAll();
}

void DateTimeEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void DateTimeEditor::setValue(const QDateTime &aValue)
{
    ui->valueDateTimeEdit->setDateTime(aValue);
}

void DateTimeEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);

    ui->valueDateTimeEdit->setToolTip(      aAttributes->stringValue("toolTip",       ui->valueDateTimeEdit->toolTip()));
    ui->valueDateTimeEdit->setMinimumDate(  aAttributes->dateValue(  "minDate",       ui->valueDateTimeEdit->minimumDate()));
    ui->valueDateTimeEdit->setMaximumDate(  aAttributes->dateValue(  "maxDate",       ui->valueDateTimeEdit->maximumDate()));
    ui->valueDateTimeEdit->setMinimumTime(  aAttributes->timeValue(  "minTime",       ui->valueDateTimeEdit->minimumTime()));
    ui->valueDateTimeEdit->setMaximumTime(  aAttributes->timeValue(  "maxTime",       ui->valueDateTimeEdit->maximumTime()));
    ui->valueDateTimeEdit->setDisplayFormat(aAttributes->stringValue("displayFormat", ui->valueDateTimeEdit->displayFormat()));
    ui->valueDateTimeEdit->setCalendarPopup(aAttributes->boolValue(  "calendarPopup", ui->valueDateTimeEdit->calendarPopup()));
}

void DateTimeEditor::on_valueDateTimeEdit_dateTimeChanged(const QDateTime &aValue)
{
    modificationDone(aValue);
}
