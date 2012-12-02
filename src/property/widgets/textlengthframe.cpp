#include "textlengthframe.h"
#include "ui_textlengthframe.h"

#include "../dialogs/textlengtheditdialog.h"

TextLengthFrame::TextLengthFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextLengthFrame)
{
    ui->setupUi(this);

    setValue(QTextLength());
}

TextLengthFrame::~TextLengthFrame()
{
    delete ui;
}

void TextLengthFrame::setUpEnabled(bool aEnabled)
{
    ui->upToolButton->setEnabled(aEnabled);
}

void TextLengthFrame::setDownEnabled(bool aEnabled)
{
    ui->downToolButton->setEnabled(aEnabled);
}

QTextLength TextLengthFrame::value() const
{
    return mTextLength;
}

void TextLengthFrame::setValue(const QTextLength &aValue)
{
    mTextLength=aValue;



    QString res="[";

    switch (mTextLength.type())
    {
        case QTextLength::VariableLength:   res.append("VariableLength");   break;
        case QTextLength::FixedLength:      res.append("FixedLength");      break;
        case QTextLength::PercentageLength: res.append("PercentageLength"); break;
    }

    res.append(", ");
    res.append(QString::number(mTextLength.rawValue()));
    res.append("]");

    ui->valueEdit->setText(res);
}

void TextLengthFrame::on_downToolButton_clicked()
{
    emit downPressed();
}

void TextLengthFrame::on_upToolButton_clicked()
{
    emit upPressed();
}

void TextLengthFrame::on_delToolButton_clicked()
{
    emit deletePressed();
}

void TextLengthFrame::on_editButton_clicked()
{
    TextLengthEditDialog dialog(mTextLength, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
    }
}