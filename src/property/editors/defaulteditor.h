#ifndef DEFAULTEDITOR_H
#define DEFAULTEDITOR_H

#include <QWidget>

namespace Ui {
class DefaultEditor;
}

class DefaultEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit DefaultEditor(QWidget *parent = 0);
    ~DefaultEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QString &aValue);

protected:
    void keyPressEvent(QKeyEvent *event);
    
private:
    Ui::DefaultEditor *ui;

private slots:
    void select();
};

#endif // DEFAULTEDITOR_H
