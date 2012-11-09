#include "rectfeditor.h"
#include "ui_rectfeditor.h"

#include "../dialogs/rectfeditdialog.h"

RectFEditor::RectFEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::RectFEditor)
{
    ui->setupUi(this);
}

RectFEditor::~RectFEditor()
{
    delete ui;
}

void RectFEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void RectFEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void RectFEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void RectFEditor::setValue(const QRectF &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           "[("+
                           QString::number(mValue.x())+
                           ", "+
                           QString::number(mValue.y())+
                           "), "+
                           QString::number(mValue.width())+
                           " x "+
                           QString::number(mValue.height())+
                           "]"
                          );
}

void RectFEditor::on_editButton_clicked()
{
    RectFEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
