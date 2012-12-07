#ifndef STRINGLISTEDITDIALOG_H
#define STRINGLISTEDITDIALOG_H

#include <QDialog>

#include <QStringList>

#include "../propertyattributes.h"

namespace Ui {
class StringListEditDialog;
}

class StringListEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StringListEditDialog(QStringList aValue, const PropertyAttributes *aAttributes, QWidget *parent=0);
    ~StringListEditDialog();

    QStringList resultValue() const;
    void setList(const QStringList &aValue);

private:
    Ui::StringListEditDialog *ui;
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
    void on_sortButton_clicked();
    void on_clearButton_clicked();
};

#endif // STRINGLISTEDITDIALOG_H
