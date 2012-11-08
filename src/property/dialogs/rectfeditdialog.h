#ifndef RECTFEDITDIALOG_H
#define RECTFEDITDIALOG_H

#include <QDialog>

namespace Ui {
class RectFEditDialog;
}

class RectFEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RectFEditDialog(QRectF aRectF, QWidget *parent = 0);
    ~RectFEditDialog();

    QRectF resultValue();

private:
    Ui::RectFEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // RECTFEDITDIALOG_H