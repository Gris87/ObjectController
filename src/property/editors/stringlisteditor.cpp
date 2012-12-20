#include "stringlisteditor.h"
#include "ui_dialogeditor.h"

#include "../dialogs/stringlisteditdialog.h"
#include "../propertyutils.h"

StringListEditor::StringListEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);
    mAttributes=0;
    mEchoMode="Normal";

#ifdef CONTROLLER_APP
    // TODO: Fix crash when you try to delete item from big amount of items
#endif
}

StringListEditor::~StringListEditor()
{
    delete ui;
}

void StringListEditor::putFocus()
{
    ui->valueEdit->setFocus();
}

void StringListEditor::selectText()
{
    ui->valueEdit->selectAll();
}

void StringListEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void StringListEditor::setValue(const QStringList &aValue)
{
    mValue=aValue;
    updateUI();
}

void StringListEditor::updateUI()
{
    ui->valueEdit->setText(stringListToString(mValue, mEchoMode));
}

void StringListEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToWidget(ui->valueEdit);



    QString aEchoMode=aAttributes->stringValue("echoMode", "Normal");

    if (mEchoMode!=aEchoMode)
    {
        mEchoMode=aEchoMode;
        updateUI();
    }
}

void StringListEditor::on_editButton_clicked()
{
    StringListEditDialog dialog(mValue, mAttributes, this);

    if (dialog.exec())
    {
        setValue(dialog.resultValue());
        emit valueChanged(mValue);
    }
}
