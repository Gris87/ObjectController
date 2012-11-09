#ifndef REGIONEDITDIALOG_H
#define REGIONEDITDIALOG_H

#include <QDialog>

#include <QRegion>

namespace Ui {
class RegionEditDialog;
}

class RegionEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegionEditDialog(QRegion aValue, QWidget *parent = 0);
    ~RegionEditDialog();

    QRegion resultValue() const;
    void setRegion(const QRegion &aValue);

private:
    Ui::RegionEditDialog *ui;

private slots:
    void itemUp();
    void itemDown();
    void itemDelete();

    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_addButton_clicked();
    void on_clearButton_clicked();
};

#endif // REGIONEDITDIALOG_H
