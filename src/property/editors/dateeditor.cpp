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

    aAttributes->applyToDateEdit(ui->valueDateEdit);
}

void DateEditor::on_valueDateEdit_dateChanged(const QDate &aValue)
{
    modificationDone(aValue);
}
