#ifndef PALETTEPREVIEWMDIAREA_H
#define PALETTEPREVIEWMDIAREA_H

#include <QMdiArea>

#include <QPalette>
#include <QMdiSubWindow>

class PalettePreviewMdiArea : public QMdiArea
{
    Q_OBJECT
public:
    explicit PalettePreviewMdiArea(QWidget *parent = 0);

    void setEnabledState();
    void setDisabledState();
    void setInactiveState();

    void setPreviewPalette(QPalette aPalette);

protected:
    QMdiSubWindow *mDemoWidget;

    void paintEvent(QPaintEvent *event);
};

#endif // PALETTEPREVIEWMDIAREA_H
