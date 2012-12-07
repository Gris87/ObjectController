#include "enumeditor.h"
#include "ui_enumeditor.h"

EnumEditor::EnumEditor(QWidget *parent) :
    CustomEditor(parent),
    ui(new Ui::EnumEditor)
{
    ui->setupUi(this);
}

EnumEditor::~EnumEditor()
{
    delete ui;
}

void EnumEditor::putFocus()
{
    ui->valueComboBox->setFocus();
}

void EnumEditor::setIcon(const QIcon &aIcon)
{
    SET_ICON(aIcon);
}

void EnumEditor::setValue(QMetaEnum *aMetaEnum, const int &aValue)
{
    mMetaEnum=aMetaEnum;

    QList<int> aValues;
    QStringList aValuesStr;
    int aIndex=-1;

    for (int i=0; i<mMetaEnum->keyCount(); ++i)
    {
        int aOneValue=mMetaEnum->value(i);

        if (!aValues.contains(aOneValue))
        {
            if (aOneValue==aValue)
            {
                aIndex=aValues.length();
            }

            aValues.append(aOneValue);
            aValuesStr.append(QString::fromLatin1(mMetaEnum->key(i)));
        }
    }

    ui->valueComboBox->clear();
    ui->valueComboBox->addItems(aValuesStr);
    ui->valueComboBox->setCurrentIndex(aIndex);
}

void EnumEditor::handleAttributes(const PropertyAttributes &aAttributes)
{
    ui->valueComboBox->setMaxVisibleItems(aAttributes.intValue("maxVisibleItems", ui->valueComboBox->maxVisibleItems()));
}

void EnumEditor::on_valueComboBox_currentIndexChanged(const QString &aValue)
{
    for (int i=0; i<mMetaEnum->keyCount(); ++i)
    {
        if (QString::fromLatin1(mMetaEnum->key(i))==aValue)
        {
            modificationDone(mMetaEnum->value(i));
        }
    }
}
