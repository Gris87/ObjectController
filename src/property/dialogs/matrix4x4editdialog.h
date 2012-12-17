#ifndef MATRIX4X4EDITDIALOG_H
#define MATRIX4X4EDITDIALOG_H

#include <QDialog>

#include <QMatrix4x4>

#include "../propertyattributes.h"

namespace Ui {
class Matrix4x4EditDialog;
}

class Matrix4x4EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Matrix4x4EditDialog(QWidget *parent = 0);
    explicit Matrix4x4EditDialog(QMatrix4x4 aMatrix4x4, QWidget *parent = 0);
    explicit Matrix4x4EditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit Matrix4x4EditDialog(QMatrix4x4 aMatrix4x4, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~Matrix4x4EditDialog();

    QMatrix4x4 resultValue();

private:
    Ui::Matrix4x4EditDialog *ui;

    void init(QMatrix4x4 aMatrix4x4, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // MATRIX4X4EDITDIALOG_H
