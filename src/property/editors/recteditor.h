#ifndef RECTEDITOR_H
#define RECTEDITOR_H

#include "customeditor.h"

#include <QRect>

namespace Ui {
class RectEditor;
}

class RectEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit RectEditor(QWidget *parent = 0);
    ~RectEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QRect &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::RectEditor *ui;
    QRect mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // RECTEDITOR_H
