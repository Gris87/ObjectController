#ifndef TRANSFORMEDITDIALOG_H
#define TRANSFORMEDITDIALOG_H

#include <QDialog>

namespace Ui {
class TransformEditDialog;
}

class TransformEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransformEditDialog(QTransform aTransform, QWidget *parent = 0);
    ~TransformEditDialog();

    QTransform resultValue();

private:
    Ui::TransformEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // TRANSFORMEDITDIALOG_H
