#ifndef POINTEDITDIALOG_H
#define POINTEDITDIALOG_H

#include <QDialog>

#include "../propertyattributes.h"

namespace Ui {
class PointEditDialog;
}

class PointEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PointEditDialog(QWidget *parent = 0);
    explicit PointEditDialog(QPoint aPoint, QWidget *parent = 0);
    explicit PointEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit PointEditDialog(QPoint aPoint, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~PointEditDialog();

    QPoint resultValue();

private:
    Ui::PointEditDialog *ui;

    void init(QPoint aPoint, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // POINTEDITDIALOG_H
