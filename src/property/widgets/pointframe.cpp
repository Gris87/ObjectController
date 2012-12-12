#include "pointframe.h"
#include "ui_pointframe.h"

#include "../dialogs/pointeditdialog.h"

PointFrame::PointFrame(const PropertyAttributes *aAttributes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PointFrame)
{
    ui->setupUi(this);

    mAttributes=aAttributes;

    setValue(QPoint(0, 0));
}

PointFrame::~PointFrame()
{
    delete ui;
}

void PointFrame::setDelEnabled(bool aEnabled)
{
    ui->delToolButton->setEnabled(aEnabled);
}

void PointFrame::setUpEnabled(bool aEnabled)
{
    ui->upToolButton->setEnabled(aEnabled);
}

void PointFrame::setDownEnabled(bool aEnabled)
{
    ui->downToolButton->setEnabled(aEnabled);
}

QPoint PointFrame::value() const
{
    return mPoint;
}

void PointFrame::setValue(const QPoint &aValue)
{
    mPoint=aValue;

    ui->valueEdit->setText(
                           "("+
                           QString::number(mPoint.x())+
                           ", "+
                           QString::number(mPoint.y())+
                           ")"
                          );
}

void PointFrame::on_downToolButton_clicked()
{
    emit downPressed();
}

void PointFrame::on_upToolButton_clicked()
{
    emit upPressed();
}

void PointFrame::on_delToolButton_clicked()
{
    emit deletePressed();
}

void PointFrame::on_editButton_clicked()
{
    PointEditDialog dialog(mPoint, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
    }
}
