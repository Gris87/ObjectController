#ifndef DATEEDITOR_H
#define DATEEDITOR_H

#include "customeditor.h"

namespace Ui {
class DateEditor;
}

class DateEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit DateEditor(QWidget *parent = 0);
    ~DateEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QDate &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DateEditor *ui;

private slots:
    void on_valueDateEdit_dateChanged(const QDate &aValue);
};

#endif // DATEEDITOR_H
