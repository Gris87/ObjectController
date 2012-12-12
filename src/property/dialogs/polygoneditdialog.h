#ifndef POLYGONEDITDIALOG_H
#define POLYGONEDITDIALOG_H

#include <QDialog>

#include <QPolygon>

#include "../propertyattributes.h"

namespace Ui {
class PolygonEditDialog;
}

class PolygonEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PolygonEditDialog(QPolygon aValue, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~PolygonEditDialog();

    QPolygon resultValue() const;
    void setPolygon(const QPolygon &aValue);

private:
    Ui::PolygonEditDialog *ui;
    const PropertyAttributes *mAttributes;
    int minCount;
    int maxCount;

    void updateCountButtons();

private slots:
    void itemUp();
    void itemDown();
    void itemDelete();

    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_addButton_clicked();
    void on_clearButton_clicked();
};

#endif // POLYGONEDITDIALOG_H
