#include "bytearrayeditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/bytearrayeditdialog.h"
#include "../propertyutils.h"

ByteArrayEditor::ByteArrayEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);
    mAttributes=0;
}

ByteArrayEditor::~ByteArrayEditor()
{
    delete ui;
}

void ByteArrayEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void ByteArrayEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void ByteArrayEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void ByteArrayEditor::setValue(const QByteArray &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(byteArrayToString(mValue));
}

void ByteArrayEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void ByteArrayEditor::on_editButton_clicked()
{
    ByteArrayEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
