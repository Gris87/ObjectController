#ifndef TEXTLENGTHEDITOR_H
#define TEXTLENGTHEDITOR_H

#include "customeditor.h"

#include <QTextLength>

namespace Ui {
class TextLengthEditor;
}

class TextLengthEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit TextLengthEditor(QWidget *parent = 0);
    ~TextLengthEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QTextLength &aValue);
    void updateUI();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::TextLengthEditor *ui;
    QTextLength mValue;
    const PropertyAttributes *mAttributes;
    int mDecimals;

private slots:
    void on_editButton_clicked();
};

#endif // TEXTLENGTHEDITOR_H
