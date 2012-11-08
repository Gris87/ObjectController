#ifndef LINEEDITOR_H
#define LINEEDITOR_H

#include "customeditor.h"

#include <QLine>

namespace Ui {
class LineEditor;
}

class LineEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit LineEditor(QWidget *parent = 0);
    ~LineEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QLine &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::LineEditor *ui;
    QLine mValue;

private slots:
    void on_editButton_clicked();
};

#endif // LINEEDITOR_H
