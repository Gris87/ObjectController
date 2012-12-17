#ifndef ICONEDITOR_H
#define ICONEDITOR_H

#include "customeditor.h"

#include <QIcon>

namespace Ui {
class DialogEditor;
}

class IconEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit IconEditor(QWidget *parent = 0);
    ~IconEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QIcon &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QIcon mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // ICONEDITOR_H
