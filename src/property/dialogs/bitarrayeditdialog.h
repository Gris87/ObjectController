#ifndef BITARRAYEDITDIALOG_H
#define BITARRAYEDITDIALOG_H

#include <QDialog>

#include <QBitArray>

#include "../widgets/biteditor.h"

namespace Ui {
class BitArrayEditDialog;
}

class BitArrayEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BitArrayEditDialog(QBitArray aValue, QWidget *parent = 0);
    ~BitArrayEditDialog();

    QBitArray resultValue() const;

private:
    Ui::BitArrayEditDialog *ui;
    BitEditor              *mBitEditor;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // BITARRAYEDITDIALOG_H
