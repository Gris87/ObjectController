#ifndef COLOREDITDIALOG_H
#define COLOREDITDIALOG_H

#include <QDialog>

#include <QColor>

#ifdef OBJECT_CONTROLLER
#include "../widgets/colorarea.h"
#include "../widgets/colorspectrum.h"
#include "../widgets/colorbar.h"
#include "../propertyattributes.h"
#else
#include "colorarea.h"
#include "colorspectrum.h"
#include "colorbar.h"
#endif

namespace Ui {
class ColorEditDialog;
}

class ColorEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorEditDialog(QWidget *parent = 0);
    explicit ColorEditDialog(QColor aColor, QWidget *parent = 0);
    explicit ColorEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit ColorEditDialog(QColor aColor, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~ColorEditDialog();

    QColor selectedColor() const;
    void setColor(const QColor &aColor);

private:
    Ui::ColorEditDialog *ui;
    ColorArea           *mMainColorArea;
    ColorSpectrum       *mColorSpectrum;
    ColorBar            *mValueColorBar;
    ColorBar            *mTransparencyColorBar;
    ColorArea           *mSelectedBasicColorArea;
    ColorArea           *mSelectedCustomColorArea;

    void init(QColor aColor, const PropertyAttributes *aAttributes);

private slots:
    void basicColorClicked();
    void customColorClicked();
    void spectrumColorChanged(QColor aColor);

    void on_hueSpinBox_valueChanged(int aValue);
    void on_satSpinBox_valueChanged(int aValue);
    void on_valSpinBox_valueChanged(int aValue);
    void on_redSpinBox_valueChanged(int aValue);
    void on_greenSpinBox_valueChanged(int aValue);
    void on_blueSpinBox_valueChanged(int aValue);
    void on_alphaSpinBox_valueChanged(int aValue);
    void on_addToCustomButton_clicked();
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // COLOREDITDIALOG_H
