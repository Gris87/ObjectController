#include "peneditor.h"
#include "ui_peneditor.h"

#include <QPainter>

#include "../dialogs/peneditdialog.h"

PenEditor::PenEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::PenEditor)
{
    ui->setupUi(this);

    ui->valueEdit->setText("Pen");
}

PenEditor::~PenEditor()
{
    delete ui;
}

void PenEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void PenEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void PenEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void PenEditor::setValue(const QPen &aValue)
{
    mValue=aValue;



    QPixmap aPenPixmap=QPixmap(16, 16);
    aPenPixmap.fill(QColor(255, 255, 255, 0));

    QPainter aPainter(&aPenPixmap);
    aPainter.setPen(mValue);
    aPainter.drawLine(aPenPixmap.width(), 0, 0, aPenPixmap.height());
    aPainter.end();

    setIcon(QIcon(aPenPixmap));
}

void PenEditor::on_editButton_clicked()
{
    PenEditDialog dialog(mValue, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
