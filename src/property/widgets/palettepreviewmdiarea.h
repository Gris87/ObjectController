#ifndef PALETTEPREVIEWMDIAREA_H
#define PALETTEPREVIEWMDIAREA_H

#include <QMdiArea>

class PalettePreviewMdiArea : public QMdiArea
{
    Q_OBJECT
public:
    explicit PalettePreviewMdiArea(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PALETTEPREVIEWMDIAREA_H
