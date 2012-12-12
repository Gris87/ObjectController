#include "sizepolicyeditor.h"
#include "ui_sizepolicyeditor.h"

#include <QMetaEnum>

#include "../dialogs/sizepolicyeditdialog.h"

SizePolicyEditor::SizePolicyEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::SizePolicyEditor)
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



    QMetaEnum aEnum=mValue.staticMetaObject.enumerator(mValue.staticMetaObject.indexOfEnumerator("Policy"));

    ui->valueEdit->setText(
                           "["+
                           QString::fromLatin1(aEnum.valueToKey(mValue.horizontalPolicy()))+
                           ", "+
                           QString::fromLatin1(aEnum.valueToKey(mValue.verticalPolicy()))+
                           ", "+
                           QString::number(mValue.horizontalStretch())+
                           ", "+
                           QString::number(mValue.verticalStretch())+
                           "]"
                          );
}

void SizePolicyEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToPalette(ui->valueEdit);
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
