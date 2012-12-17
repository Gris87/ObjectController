#ifndef TEXTLENGTHEDITDIALOG_H
#define TEXTLENGTHEDITDIALOG_H

#include <QDialog>

#include <QTextLength>

#include "../propertyattributes.h"

namespace Ui {
class TextLengthEditDialog;
}

class TextLengthEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextLengthEditDialog(QWidget *parent = 0);
    explicit TextLengthEditDialog(QTextLength aTextLength, QWidget *parent = 0);
    explicit TextLengthEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit TextLengthEditDialog(QTextLength aTextLength, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~TextLengthEditDialog();

    QTextLength resultValue();

private:
    Ui::TextLengthEditDialog *ui;

    void init(QTextLength aTextLength, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // TEXTLENGTHEDITDIALOG_H
