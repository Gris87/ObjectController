#include "sizepolicyeditdialog.h"
#include "ui_sizepolicyeditdialog.h"

#include <QMetaEnum>

SizePolicyEditDialog::SizePolicyEditDialog(QSizePolicy aSizePolicy, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizePolicyEditDialog)
{
    ui->setupUi(this);



    QMetaEnum aEnum=aSizePolicy.staticMetaObject.enumerator(aSizePolicy.staticMetaObject.indexOfEnumerator("Policy"));

    QStringList aItems;

    for (int i=0; i<aEnum.keyCount(); ++i)
    {
        aItems.append(QString::fromLatin1(aEnum.key(i)));
    }

    ui->horizontalPolicyComboBox->addItems(aItems);
    ui->verticalPolicyComboBox->addItems(aItems);



    ui->horizontalPolicyComboBox->setCurrentIndex(ui->horizontalPolicyComboBox->findText(aEnum.valueToKey(aSizePolicy.horizontalPolicy())));
    ui->verticalPolicyComboBox->setCurrentIndex(ui->verticalPolicyComboBox->findText(aEnum.valueToKey(aSizePolicy.verticalPolicy())));
    ui->horizontalStretchSpinBox->setValue(aSizePolicy.horizontalStretch());
    ui->verticalStretchSpinBox->setValue(aSizePolicy.verticalStretch());



    if (aAttributes)
    {
        aAttributes->applyToCombobox(ui->horizontalPolicyComboBox);
        aAttributes->applyToCombobox(ui->verticalPolicyComboBox);
        aAttributes->applyToSpinBox(ui->horizontalStretchSpinBox);
        aAttributes->applyToSpinBox(ui->verticalStretchSpinBox);
    }
}

SizePolicyEditDialog::~SizePolicyEditDialog()
{
    delete ui;
}

QSizePolicy SizePolicyEditDialog::resultValue() const
{
    QMetaEnum aEnum=QSizePolicy::staticMetaObject.enumerator(QSizePolicy::staticMetaObject.indexOfEnumerator("Policy"));

    QSizePolicy aPolicy;

    aPolicy.setHorizontalPolicy((QSizePolicy::Policy)aEnum.keyToValue(ui->horizontalPolicyComboBox->currentText().toLatin1()));
    aPolicy.setVerticalPolicy((QSizePolicy::Policy)aEnum.keyToValue(ui->verticalPolicyComboBox->currentText().toLatin1()));
    aPolicy.setHorizontalStretch(ui->horizontalStretchSpinBox->value());
    aPolicy.setVerticalStretch(ui->verticalStretchSpinBox->value());

    return aPolicy;
}

void SizePolicyEditDialog::on_okButton_clicked()
{
    accept();
}

void SizePolicyEditDialog::on_cancelButton_clicked()
{
    reject();
}
