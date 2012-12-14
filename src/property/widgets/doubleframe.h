#ifndef DOUBLEFRAME_H
#define DOUBLEFRAME_H

#include <QWidget>

#include "../propertyattributes.h"

namespace Ui {
    class DoubleFrame;
}

class DoubleFrame : public QWidget
{
    Q_OBJECT

public:
    explicit DoubleFrame(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~DoubleFrame();

    void setUpEnabled(bool aEnabled);
    void setDownEnabled(bool aEnabled);

    double value() const;
    void setValue(const double &aValue);

private:
    Ui::DoubleFrame *ui;

signals:
    void deletePressed();
    void upPressed();
    void downPressed();
    void valueChanged(double aValue);

private slots:
    void on_downToolButton_clicked();
    void on_upToolButton_clicked();
    void on_delToolButton_clicked();
    void on_valueSpinBox_valueChanged(double aValue);
};

#endif // DOUBLEFRAME_H
