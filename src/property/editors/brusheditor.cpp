#include "brusheditor.h"
#include "ui_dialogeditor.h"

#include <QPainter>
#include <QMetaEnum>

#include "../dialogs/brusheditdialog.h"
#include "../propertyutils.h"

BrushEditor::BrushEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

BrushEditor::~BrushEditor()
{
    delete ui;
}

void BrushEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void BrushEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void BrushEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void BrushEditor::setValue(const QBrush &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(brushToString(mValue));
    setIcon(iconForBrush(mValue));
}

void BrushEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void BrushEditor::on_editButton_clicked()
{
    BrushEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
