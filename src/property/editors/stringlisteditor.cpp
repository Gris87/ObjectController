#include "stringlisteditor.h"
#include "ui_stringlisteditor.h"

#include "../dialogs/stringlisteditdialog.h"

StringListEditor::StringListEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::StringListEditor)
{
    ui->setupUi(this);
    mAttributes=0;
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



    QString res="[";

    for (int i=0; i<mValue.length(); ++i)
    {
        res.append("\"");
        res.append(mValue.at(i));
        res.append("\"");

        if (i<mValue.length()-1)
        {
            res.append("; ");
        }
    }

    res.append("]");

    ui->valueEdit->setText(res);
}

void StringListEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    CustomEditor::handleAttributes(aAttributes);
    mAttributes=aAttributes;
    aAttributes->applyToPalette(ui->valueEdit);
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
