#ifndef LOCALEEDITOR_H
#define LOCALEEDITOR_H

#include "customeditor.h"

#include <QLocale>

namespace Ui {
class LocaleEditor;
}

class LocaleEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit LocaleEditor(QWidget *parent = 0);
    ~LocaleEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QLocale &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::LocaleEditor *ui;
    QLocale mValue;

private slots:
    void on_editButton_clicked();
};

#endif // LOCALEEDITOR_H
