#ifndef LINEFEDITDIALOG_H
#define LINEFEDITDIALOG_H

#include <QDialog>

#include "../propertyattributes.h"

namespace Ui {
class LineFEditDialog;
}

class LineFEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LineFEditDialog(QLineF aLineF, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~LineFEditDialog();

    QLineF resultValue();

private:
    Ui::LineFEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // LINEFEDITDIALOG_H
