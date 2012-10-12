#ifndef BYTEARRAYEDITDIALOG_H
#define BYTEARRAYEDITDIALOG_H

#include <QDialog>

#include <QByteArray>

#include "../widgets/hexeditor.h"

namespace Ui {
class ByteArrayEditDialog;
}

class ByteArrayEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ByteArrayEditDialog(QByteArray aValue, QWidget *parent = 0);
    ~ByteArrayEditDialog();

    QByteArray resultValue() const;

private:
    Ui::ByteArrayEditDialog *ui;
    HexEditor               *mHexEditor;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // BYTEARRAYEDITDIALOG_H
