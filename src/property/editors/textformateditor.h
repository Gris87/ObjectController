#ifndef TEXTFORMATEDITOR_H
#define TEXTFORMATEDITOR_H

#include "customeditor.h"

#include <QTextFormat>

namespace Ui {
class TextFormatEditor;
}

class TextFormatEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit TextFormatEditor(QWidget *parent = 0);
    ~TextFormatEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QTextFormat &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::TextFormatEditor *ui;
    QTextFormat mValue;

private slots:
    void on_editButton_clicked();
};

#endif // TEXTFORMATEDITOR_H
