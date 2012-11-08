#ifndef SIZEFEDITOR_H
#define SIZEFEDITOR_H

#include "customeditor.h"

#include <QSizeF>

namespace Ui {
class SizeFEditor;
}

class SizeFEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit SizeFEditor(QWidget *parent = 0);
    ~SizeFEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QSizeF &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::SizeFEditor *ui;
    QSizeF mValue;

private slots:
    void on_editButton_clicked();
};

#endif // SIZEFEDITOR_H
