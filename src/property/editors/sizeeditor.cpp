#include "sizeeditor.h"
#include "ui_sizeeditor.h"

#include "../dialogs/sizeeditdialog.h"

SizeEditor::SizeEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::SizeEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

SizeEditor::~SizeEditor()
{
    delete ui;
}

void SizeEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void SizeEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void SizeEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void SizeEditor::setValue(const QSize &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           QString::number(mValue.width())+
                           " x "+
                           QString::number(mValue.height())
                          );
}

void SizeEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void SizeEditor::on_editButton_clicked()
{
    SizeEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
