#ifndef QUATERNIONEDITDIALOG_H
#define QUATERNIONEDITDIALOG_H

#include <QDialog>

#include <QQuaternion>

#include "../propertyattributes.h"

namespace Ui {
class QuaternionEditDialog;
}

class QuaternionEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuaternionEditDialog(QQuaternion aQuaternion, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~QuaternionEditDialog();

    QQuaternion resultValue();

private:
    Ui::QuaternionEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // QUATERNIONEDITDIALOG_H
