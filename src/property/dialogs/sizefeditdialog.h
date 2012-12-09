#ifndef SIZEFEDITDIALOG_H
#define SIZEFEDITDIALOG_H

#include <QDialog>

#include "../propertyattributes.h"

namespace Ui {
class SizeFEditDialog;
}

class SizeFEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SizeFEditDialog(QSizeF aSize, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~SizeFEditDialog();

    QSizeF resultValue();

private:
    Ui::SizeFEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // SIZEFEDITDIALOG_H
