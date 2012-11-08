#ifndef LINEFEDITOR_H
#define LINEFEDITOR_H

#include "customeditor.h"

#include <QLineF>

namespace Ui {
class LineFEditor;
}

class LineFEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit LineFEditor(QWidget *parent = 0);
    ~LineFEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QLineF &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::LineFEditor *ui;
    QLineF mValue;

private slots:
    void on_editButton_clicked();
};

#endif // LINEFEDITOR_H
