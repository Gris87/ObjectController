#ifndef INTEGEREDITOR_H
#define INTEGEREDITOR_H

#include <QWidget>

namespace Ui {
class IntegerEditor;
}

class IntegerEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit IntegerEditor(QWidget *parent = 0);
    ~IntegerEditor();
    
private:
    Ui::IntegerEditor *ui;
};

#endif // INTEGEREDITOR_H
