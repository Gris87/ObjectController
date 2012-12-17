#ifndef SIZEEDITDIALOG_H
#define SIZEEDITDIALOG_H

#include <QDialog>

#include "../propertyattributes.h"

namespace Ui {
class SizeEditDialog;
}

class SizeEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SizeEditDialog(QWidget *parent = 0);
    explicit SizeEditDialog(QSize aSize, QWidget *parent = 0);
    explicit SizeEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit SizeEditDialog(QSize aSize, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~SizeEditDialog();

    QSize resultValue();

private:
    Ui::SizeEditDialog *ui;

    void init(QSize aSize, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // SIZEEDITDIALOG_H
