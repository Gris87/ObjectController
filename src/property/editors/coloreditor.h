#ifndef COLOREDITOR_H
#define COLOREDITOR_H

#include "customeditor.h"

#include <QColor>

namespace Ui {
class ColorEditor;
}

class ColorEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit ColorEditor(QWidget *parent = 0);
    ~ColorEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QColor &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::ColorEditor *ui;
    QColor mValue;

private slots:
    void on_editButton_clicked();
};

#endif // COLOREDITOR_H
