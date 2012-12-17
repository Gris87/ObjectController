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
    explicit QuaternionEditDialog(QWidget *parent = 0);
    explicit QuaternionEditDialog(QQuaternion aQuaternion, QWidget *parent = 0);
    explicit QuaternionEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit QuaternionEditDialog(QQuaternion aQuaternion, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~QuaternionEditDialog();

    QQuaternion resultValue();

private:
    Ui::QuaternionEditDialog *ui;

    void init(QQuaternion aQuaternion, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // QUATERNIONEDITDIALOG_H
