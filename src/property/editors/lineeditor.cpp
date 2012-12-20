#include "lineeditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/lineeditdialog.h"
#include "../propertyutils.h"

LineEditor::LineEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

LineEditor::~LineEditor()
{
    delete ui;
}

void LineEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void LineEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void LineEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void LineEditor::setValue(const QLine &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(lineToString(mValue));
}

void LineEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void LineEditor::on_editButton_clicked()
{
    LineEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
