#include "regioneditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/regioneditdialog.h"
#include "../propertyutils.h"

RegionEditor::RegionEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

RegionEditor::~RegionEditor()
{
    delete ui;
}

void RegionEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void RegionEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void RegionEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void RegionEditor::setValue(const QRegion &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(regionToString(mValue));
}

void RegionEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void RegionEditor::on_editButton_clicked()
{
    RegionEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
