#ifndef RECTFEDITOR_H
#define RECTFEDITOR_H

#include "customeditor.h"

#include <QRectF>

namespace Ui {
class RectFEditor;
}

class RectFEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit RectFEditor(QWidget *parent = 0);
    ~RectFEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QRectF &aValue);
    void updateUI();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::RectFEditor *ui;
    QRectF mValue;
    int mDecimals;

private slots:
    void on_editButton_clicked();
};

#endif // RECTFEDITOR_H
