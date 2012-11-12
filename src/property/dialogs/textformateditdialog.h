#ifndef TEXTFORMATEDITDIALOG_H
#define TEXTFORMATEDITDIALOG_H

#include <QDialog>

#include <QTextFormat>

namespace Ui {
class TextFormatEditDialog;
}

class TextFormatEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextFormatEditDialog(QTextFormat aTextFormat, QWidget *parent = 0);
    ~TextFormatEditDialog();

    QTextFormat resultValue() const;

private:
    Ui::TextFormatEditDialog *ui;
    QTextFormat               mTextFormat;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // TEXTFORMATEDITDIALOG_H
