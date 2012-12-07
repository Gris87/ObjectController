#include "stringframe.h"
#include "ui_stringframe.h"

#include <QMetaEnum>

StringFrame::StringFrame(const PropertyAttributes *aAttributes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StringFrame)
{
    ui->setupUi(this);

    handleAttributes(aAttributes);
}

StringFrame::~StringFrame()
{
    delete ui;
}

void StringFrame::handleAttributes(const PropertyAttributes *aAttributes)
{
    if (aAttributes)
    {
        QMetaEnum aEchoModeEnum=QLineEdit::staticMetaObject.enumerator(QLineEdit::staticMetaObject.indexOfEnumerator("EchoMode"));

        ui->valueEdit->setInputMask(      aAttributes->stringValue("inputMask",       ui->valueEdit->inputMask()));
        ui->valueEdit->setMaxLength(      aAttributes->intValue(   "maxLength",       ui->valueEdit->maxLength()));
        QString aMode =                   aAttributes->stringValue("echoMode",        QString::fromLatin1(aEchoModeEnum.valueToKey(ui->valueEdit->echoMode())));
        ui->valueEdit->setPlaceholderText(aAttributes->stringValue("placeholderText", ui->valueEdit->placeholderText()));

        for (int i=0; i<aEchoModeEnum.keyCount(); ++i)
        {
            if (QString::fromLatin1(aEchoModeEnum.key(i))==aMode)
            {
                ui->valueEdit->setEchoMode((QLineEdit::EchoMode)aEchoModeEnum.value(i));
                break;
            }
        }
    }
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
