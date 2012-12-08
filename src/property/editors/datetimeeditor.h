#ifndef DATETIMEEDITOR_H
#define DATETIMEEDITOR_H

#include "customeditor.h"

namespace Ui {
class DateTimeEditor;
}

class DateTimeEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit DateTimeEditor(QWidget *parent = 0);
    ~DateTimeEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QDateTime &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DateTimeEditor *ui;

private slots:
    void on_valueDateTimeEdit_dateTimeChanged(const QDateTime &aValue);
};

#endif // DATETIMEEDITOR_H
