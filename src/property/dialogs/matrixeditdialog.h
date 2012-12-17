#ifndef MATRIXEDITDIALOG_H
#define MATRIXEDITDIALOG_H

#include <QDialog>

#include "../propertyattributes.h"

namespace Ui {
class MatrixEditDialog;
}

class MatrixEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MatrixEditDialog(QWidget *parent = 0);
    explicit MatrixEditDialog(QMatrix aMatrix, QWidget *parent = 0);
    explicit MatrixEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit MatrixEditDialog(QMatrix aMatrix, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~MatrixEditDialog();

    QMatrix resultValue();

private:
    Ui::MatrixEditDialog *ui;

    void init(QMatrix aMatrix, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // MATRIXEDITDIALOG_H
