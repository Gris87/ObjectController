#ifndef POINTEDITDIALOG_H
#define POINTEDITDIALOG_H

#include <QDialog>

namespace Ui {
class PointEditDialog;
}

class PointEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PointEditDialog(QPoint aPoint, QWidget *parent = 0);
    ~PointEditDialog();

    QPoint resultValue();

private:
    Ui::PointEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // POINTEDITDIALOG_H