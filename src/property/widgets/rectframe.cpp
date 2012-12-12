#include "rectframe.h"
#include "ui_rectframe.h"

#include "../dialogs/recteditdialog.h"

RectFrame::RectFrame(const PropertyAttributes *aAttributes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RectFrame)
{
    ui->setupUi(this);

    mAttributes=aAttributes;

    setValue(QRect(0, 0, 0, 0));
}

RectFrame::~RectFrame()
{
    delete ui;
}

void RectFrame::setDelEnabled(bool aEnabled)
{
    ui->delToolButton->setEnabled(aEnabled);
}

void RectFrame::setUpEnabled(bool aEnabled)
{
    ui->upToolButton->setEnabled(aEnabled);
}

void RectFrame::setDownEnabled(bool aEnabled)
{
    ui->downToolButton->setEnabled(aEnabled);
}

QRect RectFrame::value() const
{
    return mRect;
}

void RectFrame::setValue(const QRect &aValue)
{
    mRect=aValue;

    ui->valueEdit->setText(
                           "[("+
                           QString::number(mRect.x())+
                           ", "+
                           QString::number(mRect.y())+
                           "), "+
                           QString::number(mRect.width())+
                           " x "+
                           QString::number(mRect.height())+
                           "]"
                          );
}

void RectFrame::on_downToolButton_clicked()
{
    emit downPressed();
}

void RectFrame::on_upToolButton_clicked()
{
    emit upPressed();
}

void RectFrame::on_delToolButton_clicked()
{
    emit deletePressed();
}

void RectFrame::on_editButton_clicked()
{
    RectEditDialog dialog(mRect, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
    }
}
