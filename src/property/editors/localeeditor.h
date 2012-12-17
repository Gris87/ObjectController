#ifndef LOCALEEDITOR_H
#define LOCALEEDITOR_H

#include "customeditor.h"

#include <QLocale>

namespace Ui {
class DialogEditor;
}

class LocaleEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit LocaleEditor(QWidget *parent = 0);
    ~LocaleEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QLocale &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QLocale mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // LOCALEEDITOR_H
