#ifndef SHORTCUTEDIT_H
#define SHORTCUTEDIT_H

#include <QLineEdit>

#include "../propertyattributes.h"

class ShortCutEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit ShortCutEdit(const PropertyAttributes *aAttributes, QWidget *parent = 0);

protected:
    QStringList mRejection;

    void keyPressEvent(QKeyEvent *event);
};

#endif // SHORTCUTEDIT_H
