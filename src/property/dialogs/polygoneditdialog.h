#ifndef POLYGONEDITDIALOG_H
#define POLYGONEDITDIALOG_H

#include <QDialog>

#include <QPolygon>

namespace Ui {
class PolygonEditDialog;
}

class PolygonEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PolygonEditDialog(QPolygon aValue, QWidget *parent = 0);
    ~PolygonEditDialog();

    QPolygon resultValue() const;
    void setPolygon(const QPolygon &aValue);

private:
    Ui::PolygonEditDialog *ui;

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
