#include "coloreditor.h"
#include "ui_coloreditor.h"

#include <QPainter>

#include "../dialogs/coloreditdialog.h"

ColorEditor::ColorEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::ColorEditor)
{
    ui->setupUi(this);
}

ColorEditor::~ColorEditor()
{
    delete ui;
}

void ColorEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void ColorEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void ColorEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void ColorEditor::setValue(const QColor &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           "("+
                           QString::number(mValue.red())+
                           ", "+
                           QString::number(mValue.green())+
                           ", "+
                           QString::number(mValue.blue())+
                           ") ["+
                           QString::number(mValue.alpha())+
                           "]"
                          );



    QColor aSolidColor(mValue.red(), mValue.green(), mValue.blue());

    QPixmap aColorPixmap=QPixmap(16, 16);
    aColorPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aColorPixmap);

    aPainter.fillRect(0, 0, aColorPixmap.width(), aColorPixmap.height(), mValue);
    aPainter.fillRect(aColorPixmap.width()>>2, aColorPixmap.height()>>2, aColorPixmap.width()>>1, aColorPixmap.height()>>1, aSolidColor);

    aPainter.end();

    setIcon(QIcon(aColorPixmap));
}

void ColorEditor::on_editButton_clicked()
{
    ColorEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.selectedColor());
        emit valueChanged(mValue);
    }
}
