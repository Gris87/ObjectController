#ifndef PALETTEDEMOWIDGET_H
#define PALETTEDEMOWIDGET_H

#include <QWidget>

namespace Ui {
class PaletteDemoWidget;
}

class PaletteDemoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaletteDemoWidget(QWidget *parent = 0);
    ~PaletteDemoWidget();

private:
    Ui::PaletteDemoWidget *ui;
};

#endif // PALETTEDEMOWIDGET_H
