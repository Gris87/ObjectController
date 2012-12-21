#ifndef LINEFEDITOR_H
#define LINEFEDITOR_H

#include "customeditor.h"

#include <QLineF>

namespace Ui {
class DialogEditor;
}

class LineFEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit LineFEditor(QWidget *parent = 0);
    ~LineFEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QLineF &aValue);
    void updateText();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QLineF mValue;
    const PropertyAttributes *mAttributes;
    int mDecimals;

private slots:
    void on_editButton_clicked();
};

#endif // LINEFEDITOR_H
