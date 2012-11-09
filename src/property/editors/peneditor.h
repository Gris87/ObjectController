#ifndef PENEDITOR_H
#define PENEDITOR_H

#include "customeditor.h"

#include <QPen>

namespace Ui {
class PenEditor;
}

class PenEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit PenEditor(QWidget *parent = 0);
    ~PenEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QPen &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::PenEditor *ui;
    QPen mValue;

private slots:
    void on_editButton_clicked();
};

#endif // PENEDITOR_H
