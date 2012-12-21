#ifndef SIZEFEDITOR_H
#define SIZEFEDITOR_H

#include "customeditor.h"

#include <QSizeF>

namespace Ui {
class DialogEditor;
}

class SizeFEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit SizeFEditor(QWidget *parent = 0);
    ~SizeFEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QSizeF &aValue);
    void updateText();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QSizeF mValue;
    const PropertyAttributes *mAttributes;
    int mDecimals;

private slots:
    void on_editButton_clicked();
};

#endif // SIZEFEDITOR_H
