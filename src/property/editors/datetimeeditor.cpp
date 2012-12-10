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

    aAttributes->applyToDateTimeEdit(ui->valueDateTimeEdit);
}

void DateTimeEditor::on_valueDateTimeEdit_dateTimeChanged(const QDateTime &aValue)
{
    modificationDone(aValue);
}
