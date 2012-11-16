#ifndef BRUSHEDITDIALOG_H
#define BRUSHEDITDIALOG_H

#include <QDialog>

#include <QBrush>

#include "../widgets/colorarea.h"
#include "../widgets/gradientwidget.h"

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
    ColorArea           *mColorArea;
    GradientWidget      *mGradientWidget;
    QLinearGradient      mLinearGradient;
    QRadialGradient      mRadialGradient;
    QConicalGradient     mConicalGradient;
    QPixmap              mTexture;
    QPixmap              mTransparentArea;

    void copyFromBrush(QBrush aBrush);
    void updateGradient();
    void updateProperties();
    void drawTexture();
    void drawBrush();
    void drawTransparentArea(QPainter *aPainter, QRect aRect, int aBoxSize=8);

private slots:
    void updateTransparentArea();
    void colorChanged(QColor aColor);
    void gradientChanged(const QGradientStops &aGradientStops);

    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_styleComboBox_currentIndexChanged(const QString &aValue);
    void on_coordinateModeComboBox_currentIndexChanged(const QString &aValue);
    void on_spreadComboBox_currentIndexChanged(const QString &aValue);
    void on_linearX1SpinBox_valueChanged(double aValue);
    void on_linearY1SpinBox_valueChanged(double aValue);
    void on_linearX2SpinBox_valueChanged(double aValue);
    void on_linearY2SpinBox_valueChanged(double aValue);
    void on_radialCenterXSpinBox_valueChanged(double aValue);
    void on_radialCenterYSpinBox_valueChanged(double aValue);
    void on_radialRadiusSpinBox_valueChanged(double aValue);
    void on_radialFocalXSpinBox_valueChanged(double aValue);
    void on_radialFocalYSpinBox_valueChanged(double aValue);
    void on_conicalCenterXSpinBox_valueChanged(double aValue);
    void on_conicalCenterYSpinBox_valueChanged(double aValue);
    void on_conicalAngleSpinBox_valueChanged(double aValue);
    void on_textureButton_clicked();
    void on_transformButton_clicked();
};

#endif // BRUSHEDITDIALOG_H
