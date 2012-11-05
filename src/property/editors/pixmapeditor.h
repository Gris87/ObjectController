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
    explicit PixmapEditor(QWidget *parent = 0);
    ~PixmapEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QPixmap &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::PixmapEditor *ui;
    QPixmap mValue;

private slots:
    void on_editButton_clicked();
};

#endif // PIXMAPEDITOR_H
