#ifndef BITARRAYEDITDIALOG_H
#define BITARRAYEDITDIALOG_H

#include <QDialog>

#include <QBitArray>

#include "../widgets/biteditor.h"
#include "../propertyattributes.h"

namespace Ui {
class BitArrayEditDialog;
}

class BitArrayEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BitArrayEditDialog(QWidget *parent = 0);
    explicit BitArrayEditDialog(QBitArray aValue, QWidget *parent = 0);
    explicit BitArrayEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit BitArrayEditDialog(QBitArray aValue, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~BitArrayEditDialog();

    QBitArray resultValue() const;

private:
    Ui::BitArrayEditDialog *ui;
    BitEditor              *mBitEditor;

    void init(QBitArray aValue, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // BITARRAYEDITDIALOG_H
