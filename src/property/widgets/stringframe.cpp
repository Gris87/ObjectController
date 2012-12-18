#include "stringframe.h"
#include "ui_stringframe.h"

StringFrame::StringFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StringFrame)
{
    init(0);
}

StringFrame::StringFrame(const PropertyAttributes *aAttributes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StringFrame)
{
    init(aAttributes);
}

void StringFrame::init(const PropertyAttributes *aAttributes)
{
    ui->setupUi(this);

    if (aAttributes)
    {
        aAttributes->applyToLineEdit(ui->valueEdit);
    }
}

StringFrame::~StringFrame()
{
    delete ui;
}

void StringFrame::setDelEnabled(bool aEnabled)
{
    ui->delToolButton->setEnabled(aEnabled);
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
    return ui->valueEdit->text();
}

void StringFrame::setValue(const QString &aValue)
{
    ui->valueEdit->setText(aValue);
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
