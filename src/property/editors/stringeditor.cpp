#include "stringeditor.h"
#include "ui_stringeditor.h"

#include <QUrl>
#include <QRegExp>
#include <QMetaEnum>

StringEditor::StringEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::StringEditor)
{
    ui->setupUi(this);

    ui->valueStackedWidget->setCurrentWidget(ui->editPage);

    connect(ui->valueComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_valueEdit_textEdited(QString)));

    mDataType=STRING;
}

StringEditor::~StringEditor()
{
    delete ui;
}

void StringEditor::putFocus()
{
    if (ui->valueStackedWidget->currentWidget()==ui->editPage)
    {
        ui->valueEdit->setFocus();
    }
    else
    if (ui->valueStackedWidget->currentWidget()==ui->comboBoxPage)
    {
        ui->valueEdit->setFocus();
    }
}

void StringEditor::selectText()
{
    if (ui->valueStackedWidget->currentWidget()==ui->editPage)
    {
        ui->valueEdit->selectAll();
    }
}

void StringEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void StringEditor::setValue(const QString &aValue)
{
    ui->valueEdit->setText(aValue);
    ui->valueStackedWidget->setCurrentWidget(ui->editPage);
    mDataType=STRING;
}

void StringEditor::setValue(const QUrl &aValue)
{
    ui->valueEdit->setText(aValue.toString());
    ui->valueStackedWidget->setCurrentWidget(ui->editPage);
    mDataType=URL;
}

void StringEditor::setValue(const QRegExp &aValue)
{
    ui->valueEdit->setText(aValue.pattern());
    ui->valueStackedWidget->setCurrentWidget(ui->editPage);
    mDataType=REGEXP;
}

void StringEditor::setValue(const QStringList &aValues, const QString &aValue)
{
    ui->valueComboBox->clear();
    ui->valueComboBox->addItems(aValues);
    ui->valueComboBox->setCurrentIndex(ui->valueComboBox->findText(aValue));

    ui->valueStackedWidget->setCurrentWidget(ui->comboBoxPage);
    mDataType=STRING;
}

void StringEditor::setValue(const QStringList &aValues, const QUrl &aValue)
{
    ui->valueComboBox->clear();
    ui->valueComboBox->addItems(aValues);
    ui->valueComboBox->setCurrentIndex(ui->valueComboBox->findText(aValue.toString()));

    ui->valueStackedWidget->setCurrentWidget(ui->comboBoxPage);
    mDataType=URL;
}

void StringEditor::setValue(const QStringList &aValues, const QRegExp &aValue)
{
    ui->valueComboBox->clear();
    ui->valueComboBox->addItems(aValues);
    ui->valueComboBox->setCurrentIndex(ui->valueComboBox->findText(aValue.pattern()));

    ui->valueStackedWidget->setCurrentWidget(ui->comboBoxPage);
    mDataType=REGEXP;
}

void StringEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    ui->valueComboBox->setMaxVisibleItems(aAttributes->intValue("maxVisibleItems", ui->valueComboBox->maxVisibleItems()));



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

void StringEditor::on_valueEdit_textEdited(const QString &aValue)
{
    switch (mDataType)
    {
        case STRING:
        {
            modificationDone(aValue);
        }
        break;
        case URL:
        {
            modificationDone(QUrl(aValue));
        }
        break;
        case REGEXP:
        {
            modificationDone(QRegExp(aValue));
        }
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
