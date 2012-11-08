#include "sizefeditor.h"
#include "ui_sizefeditor.h"

#include "../dialogs/sizefeditdialog.h"

SizeFEditor::SizeFEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::SizeFEditor)
{
    ui->setupUi(this);
}

SizeFEditor::~SizeFEditor()
{
    delete ui;
}

void SizeFEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void SizeFEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void SizeFEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void SizeFEditor::setValue(const QSizeF &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           QString::number(mValue.width())+
                           " x "+
                           QString::number(mValue.height())
                          );
}

void SizeFEditor::on_editButton_clicked()
{
    SizeFEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
