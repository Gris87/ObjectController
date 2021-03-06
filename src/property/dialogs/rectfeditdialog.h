#ifndef RECTFEDITDIALOG_H
#define RECTFEDITDIALOG_H

#include <QDialog>

#include "../propertyattributes.h"

namespace Ui {
class RectFEditDialog;
}

class RectFEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RectFEditDialog(QWidget *parent = 0);
    explicit RectFEditDialog(QRectF aRectF, QWidget *parent = 0);
    explicit RectFEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit RectFEditDialog(QRectF aRectF, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~RectFEditDialog();

    QRectF resultValue();

private:
    Ui::RectFEditDialog *ui;

    void init(QRectF aRectF, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // RECTFEDITDIALOG_H
