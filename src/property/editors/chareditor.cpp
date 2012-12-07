#include "chareditor.h"
#include "ui_chareditor.h"

#include <QMetaEnum>

CharEditor::CharEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::CharEditor)
{
    ui->setupUi(this);
}

CharEditor::~CharEditor()
{
    delete ui;
}

void CharEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void CharEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void CharEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void CharEditor::setValue(const QChar &aValue)
{
    ui->valueEdit->setText(aValue);
}

void CharEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);

    QMetaEnum aEchoModeEnum=QLineEdit::staticMetaObject.enumerator(QLineEdit::staticMetaObject.indexOfEnumerator("EchoMode"));

    ui->valueEdit->setInputMask(      aAttributes->stringValue("inputMask",       ui->valueEdit->inputMask()));
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

void CharEditor::on_valueEdit_textEdited(const QString &aValue)
{
    if (aValue.length()==0)
    {
        modificationDone(QChar());
    }
    else
    {
        modificationDone(aValue.at(0));
    }
}
