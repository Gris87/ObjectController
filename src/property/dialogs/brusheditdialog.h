#ifndef BRUSHEDITDIALOG_H
#define BRUSHEDITDIALOG_H

#include <QDialog>

#include <QBrush>

#include "../widgets/colorarea.h"

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

    void updateProperties();
    void drawTexture();
    void drawTextureImage();
    void drawBrush();

private slots:
    void colorChanged(QColor aColor);

    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_styleComboBox_currentIndexChanged(const QString &aValue);
    void on_textureButton_clicked();
    void on_textureImageButton_clicked();
    void on_matrixButton_clicked();
    void on_transformButton_clicked();
};

#endif // BRUSHEDITDIALOG_H
