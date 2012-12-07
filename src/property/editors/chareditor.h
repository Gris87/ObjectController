#ifndef CHAREDITOR_H
#define CHAREDITOR_H

#include "customeditor.h"

namespace Ui {
class CharEditor;
}

class CharEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit CharEditor(QWidget *parent = 0);
    ~CharEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QChar &aValue);
    void handleAttributes(const PropertyAttributes &aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::CharEditor *ui;

private slots:
    void on_valueEdit_textEdited(const QString &aValue);
};

#endif // CHAREDITOR_H
