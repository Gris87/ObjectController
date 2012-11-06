#include "pixmapeditor.h"
#include "ui_pixmapeditor.h"

#include "../dialogs/paintdialog.h"

PixmapEditor::PixmapEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::PixmapEditor)
{
    ui->setupUi(this);
}

PixmapEditor::~PixmapEditor()
{
    delete ui;
}

void PixmapEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void PixmapEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void PixmapEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void PixmapEditor::setValue(const QPixmap &aValue)
{
    mValue=aValue;

    ui->valueEdit->setText(
                           QString::number(aValue.width())+
                           " x "+
                           QString::number(aValue.height())
                          );

    setIcon(QIcon(aValue));
}

void PixmapEditor::on_editButton_clicked()
{
    PaintDialog dialog(mValue, false, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
