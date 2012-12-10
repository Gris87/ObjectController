#ifndef PIXMAPEDITOR_H
#define PIXMAPEDITOR_H

#include "customeditor.h"

#include <QPixmap>

namespace Ui {
class PixmapEditor;
}

class PixmapEditor : public CustomEditor
{
    Q_OBJECT

public:
    enum DataType
    {
        PIXMAP,
        IMAGE,
        BITMAP
    };

    explicit PixmapEditor(QWidget *parent = 0);
    ~PixmapEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QPixmap &aValue);
    void setValue(const QImage &aValue);
    void setValue(const QBitmap &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    DataType mDataType;

    void putFocus();
    void selectText();

private:
    Ui::PixmapEditor *ui;
    QPixmap mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // PIXMAPEDITOR_H
