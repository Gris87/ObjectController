#ifndef VECTOR4DEDITDIALOG_H
#define VECTOR4DEDITDIALOG_H

#include <QDialog>

#include <QVector4D>

#include "../propertyattributes.h"

namespace Ui {
class Vector4DEditDialog;
}

class Vector4DEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Vector4DEditDialog(QWidget *parent = 0);
    explicit Vector4DEditDialog(QVector4D aVector4D, QWidget *parent = 0);
    explicit Vector4DEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit Vector4DEditDialog(QVector4D aVector4D, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~Vector4DEditDialog();

    QVector4D resultValue();

private:
    Ui::Vector4DEditDialog *ui;

    void init(QVector4D aVector4D, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // VECTOR4DEDITDIALOG_H
