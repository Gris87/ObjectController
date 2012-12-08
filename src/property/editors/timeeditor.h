#ifndef TIMEEDITOR_H
#define TIMEEDITOR_H

#include "customeditor.h"

namespace Ui {
class TimeEditor;
}

class TimeEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit TimeEditor(QWidget *parent = 0);
    ~TimeEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QTime &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::TimeEditor *ui;

private slots:
    void on_valueTimeEdit_timeChanged(const QTime &aValue);
};

#endif // TIMEEDITOR_H
