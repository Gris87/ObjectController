#ifndef PAINTDIALOG_H
#define PAINTDIALOG_H

#include <QDialog>

#include "../widgets/paintframe.h"

namespace Ui {
class PaintDialog;
}

class PaintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaintDialog(QPixmap aValue, bool aMono, QWidget *parent = 0);
    ~PaintDialog();

    QPixmap resultValue() const;

private:
    Ui::PaintDialog *ui;
    PaintFrame      *mPaintFrame;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // PAINTDIALOG_H
