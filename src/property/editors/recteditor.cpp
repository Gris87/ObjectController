#include "recteditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/recteditdialog.h"
#include "../propertyutils.h"

RectEditor::RectEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

RectEditor::~RectEditor()
{
    delete ui;
}

void RectEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void RectEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void RectEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void RectEditor::setValue(const QRect &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(rectToString(mValue));
}

void RectEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void RectEditor::on_editButton_clicked()
{
    RectEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
