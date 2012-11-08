#ifndef RECTEDITDIALOG_H
#define RECTEDITDIALOG_H

#include <QDialog>

namespace Ui {
class RectEditDialog;
}

class RectEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RectEditDialog(QRect aRect, QWidget *parent = 0);
    ~RectEditDialog();

    QRect resultValue();

private:
    Ui::RectEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // RECTEDITDIALOG_H
