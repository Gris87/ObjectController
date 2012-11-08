#ifndef POINTFEDITDIALOG_H
#define POINTFEDITDIALOG_H

#include <QDialog>

namespace Ui {
class PointFEditDialog;
}

class PointFEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PointFEditDialog(QPointF aPointF, QWidget *parent = 0);
    ~PointFEditDialog();

    QPointF resultValue();

private:
    Ui::PointFEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // POINTFEDITDIALOG_H
