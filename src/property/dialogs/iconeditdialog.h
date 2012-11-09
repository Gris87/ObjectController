#ifndef ICONEDITDIALOG_H
#define ICONEDITDIALOG_H

#include <QDialog>

#include <QIcon>

namespace Ui {
class IconEditDialog;
}

class IconEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IconEditDialog(QIcon aIcon, QWidget *parent = 0);
    ~IconEditDialog();

    QIcon resultValue() const;

private:
    Ui::IconEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // ICONEDITDIALOG_H
