#ifndef EASINGCURVEEDITDIALOG_H
#define EASINGCURVEEDITDIALOG_H

#include <QDialog>

#include <QEasingCurve>

#include "../propertyattributes.h"

namespace Ui {
class EasingCurveEditDialog;
}

class EasingCurveEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EasingCurveEditDialog(QWidget *parent = 0);
    explicit EasingCurveEditDialog(QEasingCurve aEasingCurve, QWidget *parent = 0);
    explicit EasingCurveEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit EasingCurveEditDialog(QEasingCurve aEasingCurve, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~EasingCurveEditDialog();

    QEasingCurve resultValue() const;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::EasingCurveEditDialog *ui;
    QEasingCurve               mOriginalEasingCurve;
    QEasingCurve               mEasingCurve;

    void init(QEasingCurve aEasingCurve, const PropertyAttributes *aAttributes);

private slots:
    void drawCurve();

    void on_typeComboBox_currentIndexChanged(QString aValue);
    void on_amplitudeSpinBox_valueChanged(double aValue);
    void on_overshootSpinBox_valueChanged(double aValue);
    void on_periodSpinBox_valueChanged(double aValue);
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // EASINGCURVEEDITDIALOG_H
