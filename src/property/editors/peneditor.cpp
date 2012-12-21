#include "peneditor.h"
#include "ui_dialogeditor.h"

#include <QPainter>

#include "../dialogs/peneditdialog.h"
#include "../propertyutils.h"

PenEditor::PenEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    mAttributes=0;

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

    setIcon(iconForPen(mValue));
}

void PenEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);
}

void PenEditor::on_editButton_clicked()
{
    PenEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
