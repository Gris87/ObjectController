#ifndef FONTEDITDIALOG_H
#define FONTEDITDIALOG_H

#include <QDialog>

#include <QFont>

#include "../propertyattributes.h"

namespace Ui {
class FontEditDialog;
}

class FontEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FontEditDialog(QWidget *parent = 0);
    explicit FontEditDialog(QFont aFont, QWidget *parent = 0);
    explicit FontEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit FontEditDialog(QFont aFont, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~FontEditDialog();

    void setCurrentFont(const QFont &font);
    QFont currentFont() const;

    QFont selectedFont() const;

protected:
    bool eventFilter(QObject *object, QEvent *event);

    void updateFamilies();
    void updateStyles();
    void updateSizes();
    void updateSample();

private:
    Ui::FontEditDialog *ui;
    QFont mFont;
    int mMinSize;
    int mMaxSize;

    void init(QFont aFont, const PropertyAttributes *aAttributes);

private slots:
    void on_writingSystemComboBox_activated(int index);
    void on_strikeoutCheckBox_toggled(bool checked);
    void on_underlineCheckBox_toggled(bool checked);
    void on_familyList_currentTextChanged(const QString &currentText);
    void on_styleList_currentTextChanged(const QString &currentText);
    void on_sizeList_currentTextChanged(const QString &currentText);
    void on_sizeEdit_textChanged(const QString &aValue);
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // FONTEDITDIALOG_H
