#ifndef SHORTCUTEDIT_H
#define SHORTCUTEDIT_H

#include <QLineEdit>

class ShortCutEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit ShortCutEdit(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // SHORTCUTEDIT_H
