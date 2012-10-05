#ifndef BITARRAYEDITDIALOG_H
#define BITARRAYEDITDIALOG_H

#include <QDialog>

#include <QBitArray>

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
};

#endif // BITARRAYEDITDIALOG_H
