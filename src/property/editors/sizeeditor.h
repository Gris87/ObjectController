#ifndef SIZEEDITOR_H
#define SIZEEDITOR_H

#include "customeditor.h"

#include <QSize>

namespace Ui {
class SizeEditor;
}

class SizeEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit SizeEditor(QWidget *parent = 0);
    ~SizeEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QSize &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::SizeEditor *ui;
    QSize mValue;

private slots:
    void on_editButton_clicked();
};

#endif // SIZEEDITOR_H
