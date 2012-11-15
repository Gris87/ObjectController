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

    void copyFromBrush(QBrush aBrush);
    void updateProperties();
    void drawTexture();
    void drawBrush();
    void drawTransparentArea(QPainter *aPainter, QRect aRect, int aBoxSize=8);

private slots:
    void colorChanged(QColor aColor);

    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_styleComboBox_currentIndexChanged(const QString &aValue);
    void on_textureButton_clicked();
    void on_transformButton_clicked();
};

#endif // BRUSHEDITDIALOG_H
