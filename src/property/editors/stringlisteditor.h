#ifndef STRINGLISTEDITOR_H
#define STRINGLISTEDITOR_H

#include "customeditor.h"

#include <QStringList>

namespace Ui {
class StringListEditor;
}

class StringListEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit StringListEditor(QWidget *parent = 0);
    ~StringListEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QStringList &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::StringListEditor *ui;
    QStringList mValue;

private slots:
    void on_editButton_clicked();
};

#endif // STRINGLISTEDITOR_H