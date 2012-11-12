#ifndef VECTOR2DEDITDIALOG_H
#define VECTOR2DEDITDIALOG_H

#include <QDialog>

#include <QVector2D>

namespace Ui {
class Vector2DEditDialog;
}

class Vector2DEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Vector2DEditDialog(QVector2D aVector2D, QWidget *parent = 0);
    ~Vector2DEditDialog();

    QVector2D resultValue();

private:
    Ui::Vector2DEditDialog *ui;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // VECTOR2DEDITDIALOG_H
