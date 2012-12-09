#ifndef LINEEDITDIALOG_H
#define LINEEDITDIALOG_H

#include <QDialog>

#include "../propertyattributes.h"

namespace Ui {
class LineEditDialog;
}

class LineEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LineEditDialog(QLine aLine, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~LineEditDialog();

    QLine resultValue();

private:
    Ui::LineEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // LINEEDITDIALOG_H
