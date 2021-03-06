#ifndef TRANSFORMEDITDIALOG_H
#define TRANSFORMEDITDIALOG_H

#include <QDialog>

#include "../propertyattributes.h"

namespace Ui {
class TransformEditDialog;
}

class TransformEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransformEditDialog(QWidget *parent = 0);
    explicit TransformEditDialog(QTransform aTransform, QWidget *parent = 0);
    explicit TransformEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit TransformEditDialog(QTransform aTransform, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~TransformEditDialog();

    QTransform resultValue();

private:
    Ui::TransformEditDialog *ui;

    void init(QTransform aTransform, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // TRANSFORMEDITDIALOG_H
