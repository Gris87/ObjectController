#ifndef SIZEEDITDIALOG_H
#define SIZEEDITDIALOG_H

#include <QDialog>

namespace Ui {
class SizeEditDialog;
}

class SizeEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SizeEditDialog(QSize aSize, QWidget *parent = 0);
    ~SizeEditDialog();

    QSize resultValue();

private:
    Ui::SizeEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // SIZEEDITDIALOG_H
