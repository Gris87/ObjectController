#ifndef SIZEPOLICYEDITDIALOG_H
#define SIZEPOLICYEDITDIALOG_H

#include <QDialog>

#include <QSizePolicy>

namespace Ui {
class SizePolicyEditDialog;
}

class SizePolicyEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SizePolicyEditDialog(QSizePolicy aSizePolicy, QWidget *parent = 0);
    ~SizePolicyEditDialog();

    QSizePolicy resultValue() const;

private:
    Ui::SizePolicyEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // SIZEPOLICYEDITDIALOG_H
