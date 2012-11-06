#ifndef PALETTEEDITDIALOG_H
#define PALETTEEDITDIALOG_H

#include <QDialog>

#include <QPalette>

namespace Ui {
class PaletteEditDialog;
}

class PaletteEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaletteEditDialog(QPalette aPalette, QWidget *parent = 0);
    ~PaletteEditDialog();

    QPalette resultValue() const;

private:
    Ui::PaletteEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // PALETTEEDITDIALOG_H
