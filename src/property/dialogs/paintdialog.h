#ifndef PAINTDIALOG_H
#define PAINTDIALOG_H

#include <QDialog>

#include "../widgets/paintframe.h"
#include "../propertyattributes.h"

namespace Ui {
class PaintDialog;
}

class PaintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaintDialog(QWidget *parent = 0);
    explicit PaintDialog(QPixmap aValue, QWidget *parent = 0);
    explicit PaintDialog(QPixmap aValue, bool aMono, QWidget *parent = 0);
    explicit PaintDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit PaintDialog(bool aMono, QWidget *parent = 0);
    explicit PaintDialog(bool aMono, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit PaintDialog(QPixmap aValue, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit PaintDialog(QPixmap aValue, bool aMono, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~PaintDialog();

    QPixmap resultValue() const;

private:
    Ui::PaintDialog *ui;
    PaintFrame      *mPaintFrame;

    void init(QPixmap aValue, bool aMono, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_actionOpen_triggered();
    void on_actionResize_triggered();
    void on_actionPlus_triggered();
    void on_actionMinus_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
};

#endif // PAINTDIALOG_H
