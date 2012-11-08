#ifndef COLOREDITDIALOG_H
#define COLOREDITDIALOG_H

#include <QDialog>

#include <QColor>

#include "../widgets/colorarea.h"
#include "../widgets/colorspectrum.h"
#include "../widgets/colorbar.h"

namespace Ui {
class ColorEditDialog;
}

class ColorEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorEditDialog(QColor aColor=QColor(0, 0, 0), QWidget *parent = 0);
    ~ColorEditDialog();

    QColor resultValue() const;

private:
    Ui::ColorEditDialog *ui;
    ColorArea           *mMainColorArea;
    ColorSpectrum       *mColorSpectrum;
    ColorBar            *mValueColorBar;
    ColorBar            *mTransparencyColorBar;
    ColorArea           *mSelectedBasicColorArea;
    ColorArea           *mSelectedCustomColorArea;

    void setColor(QColor aColor);

private slots:
    void basicColorClicked();
    void customColorClicked();
    void spectrumColorChanged(QColor aColor);

    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_hueSpinBox_valueChanged(int aValue);
    void on_satSpinBox_valueChanged(int aValue);
    void on_valSpinBox_valueChanged(int aValue);
    void on_redSpinBox_valueChanged(int aValue);
    void on_greenSpinBox_valueChanged(int aValue);
    void on_blueSpinBox_valueChanged(int aValue);
    void on_alphaSpinBox_valueChanged(int aValue);
    void on_addToCustomButton_clicked();
};

#endif // COLOREDITDIALOG_H
