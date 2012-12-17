#ifndef LOCALEEDITDIALOG_H
#define LOCALEEDITDIALOG_H

#include <QDialog>

#include <QLocale>

#include "../propertyattributes.h"

namespace Ui {
class LocaleEditDialog;
}

class LocaleEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LocaleEditDialog(QWidget *parent = 0);
    explicit LocaleEditDialog(QLocale aLocale, QWidget *parent = 0);
    explicit LocaleEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit LocaleEditDialog(QLocale aLocale, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~LocaleEditDialog();

    QLocale resultValue() const;

private:
    Ui::LocaleEditDialog *ui;
    QLocale               mLocale;

    void init(QLocale aLocale, const PropertyAttributes *aAttributes);

    QLocale::Language stringToLanguage(const QString &aLanguage);
    QLocale::Country stringToCountry(const QString &aCountry);

    void updateLanguages();
    void updateCountries();
    void updateValues();

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_languageComboBox_currentIndexChanged(const QString &aValue);
    void on_countryComboBox_currentIndexChanged(const QString &aValue);
};

#endif // LOCALEEDITDIALOG_H
