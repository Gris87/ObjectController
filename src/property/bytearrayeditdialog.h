#ifndef BYTEARRAYEDITDIALOG_H
#define BYTEARRAYEDITDIALOG_H

#include <QDialog>

#include <QByteArray>

namespace Ui {
class ByteArrayEditDialog;
}

class ByteArrayEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ByteArrayEditDialog(QWidget *parent = 0);
    ~ByteArrayEditDialog();

    QByteArray resultValue() const;

private:
    Ui::ByteArrayEditDialog *ui;
};

#endif // BYTEARRAYEDITDIALOG_H
