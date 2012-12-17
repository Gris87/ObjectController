#ifndef POINTFEDITDIALOG_H
#define POINTFEDITDIALOG_H

#include <QDialog>

#include "../propertyattributes.h"

namespace Ui {
class PointFEditDialog;
}

class PointFEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PointFEditDialog(QWidget *parent = 0);
    explicit PointFEditDialog(QPointF aPointF, QWidget *parent = 0);
    explicit PointFEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit PointFEditDialog(QPointF aPointF, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~PointFEditDialog();

    QPointF resultValue();

private:
    Ui::PointFEditDialog *ui;

    void init(QPointF aPointF, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // POINTFEDITDIALOG_H
