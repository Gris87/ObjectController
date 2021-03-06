#include "pointeditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/pointeditdialog.h"
#include "../propertyutils.h"

PointEditor::PointEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

PointEditor::~PointEditor()
{
    delete ui;
}

void PointEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void PointEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void PointEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void PointEditor::setValue(const QPoint &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(pointToString(mValue));
}

void PointEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void PointEditor::on_editButton_clicked()
{
    PointEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
