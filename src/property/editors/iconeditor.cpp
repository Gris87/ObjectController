#include "iconeditor.h"
#include "ui_iconeditor.h"

#include "../dialogs/iconeditdialog.h"

IconEditor::IconEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::IconEditor)
{
    ui->setupUi(this);

    mAttributes=0;

    ui->valueEdit->setText("Icon");
}

IconEditor::~IconEditor()
{
    delete ui;
}

void IconEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void IconEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void IconEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void IconEditor::setValue(const QIcon &aValue)
{
    mValue=aValue;

    setIcon(mValue);
}

void IconEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void IconEditor::on_editButton_clicked()
{
    IconEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
