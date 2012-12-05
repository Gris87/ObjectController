#ifndef STRINGEDITOR_H
#define STRINGEDITOR_H

#include "customeditor.h"

namespace Ui {
class StringEditor;
}

class StringEditor : public CustomEditor
{
    Q_OBJECT

public:
    enum DataType
    {
        STRING,
        URL,
        REGEXP
    };

    explicit StringEditor(QWidget *parent = 0);
    ~StringEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QString &aValue);
    void setValue(const QUrl &aValue);
    void setValue(const QRegExp &aValue);
    void setValue(const QStringList &aValues, const QString &aValue);
    void setValue(const QStringList &aValues, const QUrl &aValue);
    void setValue(const QStringList &aValues, const QRegExp &aValue);

protected:
    DataType mDataType;

    void putFocus();
    void selectText();

private:
    Ui::StringEditor *ui;

private slots:
    void on_valueEdit_textEdited(const QString &aValue);
};

#endif // STRINGEDITOR_H
