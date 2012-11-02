#include "stringeditor.h"
#include "ui_stringeditor.h"

#include <QUrl>
#include <QRegExp>

StringEditor::StringEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::StringEditor)
{
    ui->setupUi(this);

    mDataType=STRING;
}

StringEditor::~StringEditor()
{
    delete ui;
}

void StringEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void StringEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void StringEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void StringEditor::setValue(const QString &aValue)
{
    ui->valueEdit->setText(aValue);
    mDataType=STRING;
}

void StringEditor::setValue(const QUrl &aValue)
{
    ui->valueEdit->setText(aValue.toString());
    mDataType=URL;
}

void StringEditor::setValue(const QRegExp &aValue)
{
    ui->valueEdit->setText(aValue.pattern());
    mDataType=REGEXP;
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
