#include "stringframe.h"
#include "ui_stringframe.h"

StringFrame::StringFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StringFrame)
{
    ui->setupUi(this);
}

StringFrame::~StringFrame()
{
    delete ui;
}

void StringFrame::setUpEnabled(bool aEnabled)
{
    ui->upToolButton->setEnabled(aEnabled);
}

void StringFrame::setDownEnabled(bool aEnabled)
{
    ui->downToolButton->setEnabled(aEnabled);
}

QString StringFrame::value() const
{
    return ui->valueEdit->toPlainText();
}

void StringFrame::setValue(const QString &aValue)
{
    ui->valueEdit->setPlainText(aValue);
}

void StringFrame::on_downToolButton_clicked()
{
    emit downPressed();
}

void StringFrame::on_upToolButton_clicked()
{
    emit upPressed();
}

void StringFrame::on_delToolButton_clicked()
{
    emit deletePressed();
}
