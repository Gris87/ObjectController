#include "localeeditdialog.h"
#include "ui_localeeditdialog.h"

#include <QTime>
#include <QMetaEnum>

LocaleEditDialog::LocaleEditDialog(QLocale aLocale, const PropertyAttributes *aAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocaleEditDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    mLocale=aLocale;

    updateLanguages();
    updateCountries();
    updateValues();

    if (aAttributes)
    {
        aAttributes->applyToWidget(ui->numberEdit);
        aAttributes->applyToWidget(ui->currencyEdit);
        aAttributes->applyToWidget(ui->timeEdit);
        aAttributes->applyToWidget(ui->shortDateEdit);
        aAttributes->applyToWidget(ui->longDateEdit);

        aAttributes->applyToCombobox(ui->languageComboBox);
        aAttributes->applyToCombobox(ui->countryComboBox);
    }
}

LocaleEditDialog::~LocaleEditDialog()
{
    delete ui;
}

QLocale LocaleEditDialog::resultValue() const
{
    return mLocale;
}

void LocaleEditDialog::on_okButton_clicked()
{
    accept();
}

void LocaleEditDialog::on_cancelButton_clicked()
{
    reject();
}

void LocaleEditDialog::on_languageComboBox_currentIndexChanged(const QString &aValue)
{
    mLocale=QLocale(stringToLanguage(aValue), mLocale.country());
    updateCountries();
    updateValues();
}

void LocaleEditDialog::on_countryComboBox_currentIndexChanged(const QString &aValue)
{
    mLocale=QLocale(mLocale.language(), stringToCountry(aValue));
    updateValues();
}

QLocale::Language LocaleEditDialog::stringToLanguage(const QString &aLanguage)
{
    QMetaEnum aLanguageEnum=mLocale.staticMetaObject.enumerator(mLocale.staticMetaObject.indexOfEnumerator("Language"));
    return (QLocale::Language)aLanguageEnum.keysToValue(aLanguage.toLatin1());
}

QLocale::Country LocaleEditDialog::stringToCountry(const QString &aCountry)
{
    QMetaEnum aCountryEnum=mLocale.staticMetaObject.enumerator(mLocale.staticMetaObject.indexOfEnumerator("Country"));
    return (QLocale::Country)aCountryEnum.keysToValue(aCountry.toLatin1());
}

void LocaleEditDialog::updateLanguages()
{
    ui->languageComboBox->blockSignals(true);

    ui->languageComboBox->clear();

    QMetaEnum aLanguageEnum=mLocale.staticMetaObject.enumerator(mLocale.staticMetaObject.indexOfEnumerator("Language"));

    QList<QLocale::Language> aLanguages;

    for (int i=0; i<aLanguageEnum.keyCount(); ++i)
    {
        QLocale::Language aOneLanguage=(QLocale::Language)aLanguageEnum.keyToValue(aLanguageEnum.key(i));

        if (!aLanguages.contains(aOneLanguage))
        {
            aLanguages.append(aOneLanguage);
        }
    }



    if (aLanguages.length()>0)
    {
        QStringList aItems;

        for (int i=0; i<aLanguages.length(); ++i)
        {
            aItems.append(aLanguageEnum.valueToKey(aLanguages.at(i)));
        }

        aItems.sort();
        ui->languageComboBox->addItems(aItems);

        int index=aItems.indexOf(aLanguageEnum.valueToKey(mLocale.language()));

        if (index>=0)
        {
            ui->languageComboBox->setCurrentIndex(index);
        }
        else
        {
            mLocale=QLocale(stringToLanguage(aItems.at(0)), mLocale.country());
            ui->languageComboBox->setCurrentIndex(0);
        }
    }

    ui->languageComboBox->blockSignals(false);
}

void LocaleEditDialog::updateCountries()
{
    ui->countryComboBox->blockSignals(true);

    ui->countryComboBox->clear();

    QMetaEnum aCountryEnum=mLocale.staticMetaObject.enumerator(mLocale.staticMetaObject.indexOfEnumerator("Country"));

    QList<QLocale::Country> aCountries=QLocale::countriesForLanguage(mLocale.language());

    for (int i=0; i<aCountries.length(); ++i)
    {
        if (aCountries.indexOf(aCountries.at(i))<i)
        {
            aCountries.removeAt(i);
            --i;
        }
    }



    if (aCountries.length()>0)
    {
        QStringList aItems;

        for (int i=0; i<aCountries.length(); ++i)
        {
            aItems.append(aCountryEnum.valueToKey(aCountries.at(i)));
        }

        aItems.sort();
        ui->countryComboBox->addItems(aItems);

        int index=aItems.indexOf(aCountryEnum.valueToKey(mLocale.country()));

        if (index>=0)
        {
            ui->countryComboBox->setCurrentIndex(index);
        }
        else
        {
            mLocale=QLocale(mLocale.language(), stringToCountry(aItems.at(0)));
            ui->countryComboBox->setCurrentIndex(0);
        }
    }

    ui->countryComboBox->blockSignals(false);
}

void LocaleEditDialog::updateValues()
{
    ui->numberEdit->setText(mLocale.toString(123456789.0f, 'f', 2));
    ui->currencyEdit->setText(mLocale.toCurrencyString(123456789.0f));
    ui->timeEdit->setText(mLocale.toString(QTime::currentTime(), QLocale::ShortFormat));
    ui->shortDateEdit->setText(mLocale.toString(QDate::currentDate(), QLocale::ShortFormat));
    ui->longDateEdit->setText(mLocale.toString(QDate::currentDate(), QLocale::LongFormat));
}
