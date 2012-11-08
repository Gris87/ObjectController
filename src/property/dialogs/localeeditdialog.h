#ifndef LOCALEEDITDIALOG_H
#define LOCALEEDITDIALOG_H

#include <QDialog>

#include <QLocale>

namespace Ui {
class LocaleEditDialog;
}

class LocaleEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LocaleEditDialog(QLocale aLocale, QWidget *parent = 0);
    ~LocaleEditDialog();

    QLocale resultValue() const;

private:
    Ui::LocaleEditDialog *ui;
    QLocale               mLocale;

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
