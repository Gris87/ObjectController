#ifndef BITARRAYDIALOG_H
#define BITARRAYDIALOG_H

#include <QDialog>

#include <QBitArray>

namespace Ui {
class BitArrayDialog;
}

class BitArrayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BitArrayDialog(QWidget *parent = 0);
    ~BitArrayDialog();

    QBitArray resultValue() const;

private:
    Ui::BitArrayDialog *ui;
};

#endif // BITARRAYDIALOG_H
