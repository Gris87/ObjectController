#ifndef MATRIXEDITDIALOG_H
#define MATRIXEDITDIALOG_H

#include <QDialog>

namespace Ui {
class MatrixEditDialog;
}

class MatrixEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MatrixEditDialog(QMatrix aMatrix, QWidget *parent = 0);
    ~MatrixEditDialog();

    QMatrix resultValue();

private:
    Ui::MatrixEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // MATRIXEDITDIALOG_H
