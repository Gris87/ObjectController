#include "sizepolicyeditor.h"
#include "ui_dialogeditor.h"

#include <QMetaEnum>

#include "../dialogs/sizepolicyeditdialog.h"
#include "../propertyutils.h"

SizePolicyEditor::SizePolicyEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

SizePolicyEditor::~SizePolicyEditor()
{
    delete ui;
}

void SizePolicyEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void SizePolicyEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void SizePolicyEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void SizePolicyEditor::setValue(const QSizePolicy &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(sizePolicyToString(mValue));
}

void SizePolicyEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void SizePolicyEditor::on_editButton_clicked()
{
    SizePolicyEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
