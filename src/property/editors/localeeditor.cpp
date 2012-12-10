#include "localeeditor.h"
#include "ui_localeeditor.h"

#include "../dialogs/localeeditdialog.h"

LocaleEditor::LocaleEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::LocaleEditor)
{
    ui->setupUi(this);

    mAttributes=0;
}

LocaleEditor::~LocaleEditor()
{
    delete ui;
}

void LocaleEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void LocaleEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void LocaleEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void LocaleEditor::setValue(const QLocale &aValue)
{
    mValue=aValue;



    ui->valueEdit->setText(
                           mValue.languageToString(mValue.language())+
                           ", "+
                           mValue.countryToString(mValue.country())
                          );
}

void LocaleEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
}

void LocaleEditor::on_editButton_clicked()
{
    LocaleEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
