#ifndef PALETTEEDITDIALOG_H
#define PALETTEEDITDIALOG_H

#include <QDialog>

#include <QPalette>
#include <QMdiSubWindow>

#include "../widgets/palettepreviewmdiarea.h"
#include "../propertyattributes.h"

namespace Ui {
class PaletteEditDialog;
}

class PaletteEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaletteEditDialog(QWidget *parent = 0);
    explicit PaletteEditDialog(QPalette aPalette, QWidget *parent = 0);
    explicit PaletteEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit PaletteEditDialog(QPalette aPalette, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~PaletteEditDialog();

    QPalette resultValue() const;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::PaletteEditDialog *ui;
    QMdiSubWindow         *mDemoWidget;
    PalettePreviewMdiArea *mPreviewArea;

    void init(QPalette aPalette, const PropertyAttributes *aAttributes);

    void calculateColor(int aRow, QColor aColor);

private slots:
    void fastColorChanged(QColor aColor);
    void colorChanged(QColor aColor);
    void updateColumns();
    void updateDemo();

    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_calculateDetailsRadioButton_toggled(bool checked);
    void on_showDetailsRadioButton_toggled(bool checked);
    void on_enabledRadioButton_toggled(bool checked);
    void on_disabledRadioButton_toggled(bool checked);
    void on_inactiveRadioButton_toggled(bool checked);
};

#endif // PALETTEEDITDIALOG_H
