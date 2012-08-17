#ifndef COMBOBOXWITHENTER_H
#define COMBOBOXWITHENTER_H

#include <QComboBox>

#include <QKeyEvent>

class ComboBoxWithEnter : public QComboBox
{
    Q_OBJECT
public:
    explicit ComboBoxWithEnter(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *e);

signals:
    void enterPressed();
};

#endif // COMBOBOXWITHENTER_H
