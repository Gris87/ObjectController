#ifndef ICONEDITOR_H
#define ICONEDITOR_H

#include "customeditor.h"

#include <QIcon>

namespace Ui {
class IconEditor;
}

class IconEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit IconEditor(QWidget *parent = 0);
    ~IconEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QIcon &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::IconEditor *ui;
    QIcon mValue;

private slots:
    void on_editButton_clicked();
};

#endif // ICONEDITOR_H
