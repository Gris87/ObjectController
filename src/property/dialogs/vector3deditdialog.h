#ifndef VECTOR3DEDITDIALOG_H
#define VECTOR3DEDITDIALOG_H

#include <QDialog>

#include <QVector3D>

#include "../propertyattributes.h"

namespace Ui {
class Vector3DEditDialog;
}

class Vector3DEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Vector3DEditDialog(QVector3D aVector3D, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~Vector3DEditDialog();

    QVector3D resultValue();

private:
    Ui::Vector3DEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // VECTOR3DEDITDIALOG_H
