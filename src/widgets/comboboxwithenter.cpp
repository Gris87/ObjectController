#include "comboboxwithenter.h"

ComboBoxWithEnter::ComboBoxWithEnter(QWidget *parent) :
    QComboBox(parent)
{
}

void ComboBoxWithEnter::keyPressEvent(QKeyEvent *e)
{
    if (e->key()==Qt::Key_Return || e->key()==Qt::Key_Enter)
    {
        emit enterPressed();
    }
    else
    {
        QComboBox::keyPressEvent(e);
    }
}
