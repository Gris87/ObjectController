#ifndef TEXTLENGTHEDITDIALOG_H
#define TEXTLENGTHEDITDIALOG_H

#include <QDialog>

#include <QTextLength>

namespace Ui {
class TextLengthEditDialog;
}

class TextLengthEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextLengthEditDialog(QTextLength aTextLength, QWidget *parent = 0);
    ~TextLengthEditDialog();

    QTextLength resultValue();

private:
    Ui::TextLengthEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // TEXTLENGTHEDITDIALOG_H
