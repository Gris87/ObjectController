#ifndef STRINGLISTEDITDIALOG_H
#define STRINGLISTEDITDIALOG_H

#include <QDialog>

#include <QStringList>

namespace Ui {
class StringListEditDialog;
}

class StringListEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StringListEditDialog(QStringList aValue, QWidget *parent = 0);
    ~StringListEditDialog();

    QStringList resultValue() const;
    void setList(const QStringList &aValue);

private:
    Ui::StringListEditDialog *ui;

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
