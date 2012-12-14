#ifndef PENEDITDIALOG_H
#define PENEDITDIALOG_H

#include <QDialog>

#include <QPen>

#include "../widgets/colorarea.h"
#include "../propertyattributes.h"

namespace Ui {
class PenEditDialog;
}

class PenEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PenEditDialog(QPen aPen, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~PenEditDialog();

    QPen resultValue() const;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::PenEditDialog *ui;
    QPen               mPen;
    ColorArea         *mColorArea;
    const PropertyAttributes *mAttributes;

    void updateProperties(const bool &aNeedToUpdatePattern=true);
    void updatePattern();
    void addPattern();
    void drawBrush();

private slots:
    void drawPen();
    void colorChanged(QColor aColor);
    void patternUp();
    void patternDown();
    void patternDelete();
    void patternValueChanged(double aValue);

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
    void on_addButton_clicked();
};

#endif // PENEDITDIALOG_H
