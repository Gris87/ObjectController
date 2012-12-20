#include "polygoneditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/polygoneditdialog.h"
#include "../propertyutils.h"

PolygonEditor::PolygonEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

PolygonEditor::~PolygonEditor()
{
    delete ui;
}

void PolygonEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void PolygonEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void PolygonEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void PolygonEditor::setValue(const QPolygon &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(polygonToString(mValue));
}

void PolygonEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void PolygonEditor::on_editButton_clicked()
{
    PolygonEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
