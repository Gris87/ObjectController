#ifndef BRUSHEDITDIALOG_H
#define BRUSHEDITDIALOG_H

#include <QDialog>

#include <QBrush>

namespace Ui {
class BrushEditDialog;
}

class BrushEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BrushEditDialog(QBrush aBrush, QWidget *parent = 0);
    ~BrushEditDialog();

    QBrush resultValue() const;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::BrushEditDialog *ui;
    QBrush               mBrush;

    void drawBrush();

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // BRUSHEDITDIALOG_H
