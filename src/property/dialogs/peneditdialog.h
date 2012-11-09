#ifndef PENEDITDIALOG_H
#define PENEDITDIALOG_H

#include <QDialog>

#include <QPen>

#include "../widgets/colorarea.h"

namespace Ui {
class PenEditDialog;
}

class PenEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PenEditDialog(QPen aPen, QWidget *parent = 0);
    ~PenEditDialog();

    QPen resultValue() const;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::PenEditDialog *ui;
    QPen               mPen;
    ColorArea         *mColorArea;

    void drawBrush();
    void drawPen();

private slots:
    void colorChanged(QColor aColor);

    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_brushButton_clicked();
    void on_widthSpinBox_valueChanged(double aValue);
    void on_styleComboBox_currentIndexChanged(const QString &aValue);
    void on_capStyleComboBox_currentIndexChanged(const QString &aValue);
    void on_joinStyleComboBox_currentIndexChanged(const QString &aValue);
    void on_cosmeticCheckBox_toggled(bool aChecked);
    void on_milerLimitSpinBox_valueChanged(double aValue);
    void on_dashOffsetSpinBox_valueChanged(double aValue);
};

#endif // PENEDITDIALOG_H
