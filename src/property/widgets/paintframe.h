#ifndef PAINTFRAME_H
#define PAINTFRAME_H

#include <QWidget>

#include "colorarea.h"
#include "paintview.h"

#include "../propertyattributes.h"

namespace Ui {
class PaintFrame;
}

class PaintFrame : public QWidget
{
    Q_OBJECT

public:
    explicit PaintFrame(QWidget *parent = 0);
    explicit PaintFrame(QPixmap aValue, QWidget *parent = 0);
    explicit PaintFrame(QPixmap aValue, bool aMono, QWidget *parent = 0);
    explicit PaintFrame(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit PaintFrame(bool aMono, QWidget *parent = 0);
    explicit PaintFrame(bool aMono, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit PaintFrame(QPixmap aValue, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit PaintFrame(QPixmap aValue, bool aMono, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~PaintFrame();

    QPixmap image() const;

    PaintView* getImageView();

private:
    Ui::PaintFrame *ui;
    PaintView      *mImageView;
    ColorArea      *mLeftArea;
    ColorArea      *mRightArea;
    const PropertyAttributes *mAttributes;

    void init(QPixmap aValue, bool aMono, const PropertyAttributes *aAttributes);

private slots:
    void colorLeftSelected();
    void colorRightSelected();
    void leftColorChanged(QColor aColor);
    void rightColorChanged(QColor aColor);

public slots:
    void on_openButton_clicked();
    void on_resizeButton_clicked();
};

#endif // PAINTFRAME_H
